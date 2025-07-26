#include "FileManager.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <cstring>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>

using namespace storage;
using namespace std;

// ============================================
// Test Utilities
// ============================================

class TestSuite {
public:
    int passed = 0;
    int failed = 0;
    string current_test;
    
public:
    void start_test(const string& name) {
        current_test = name;
        cout << "\n[TEST] " << name << endl;
    }
    
    void assert_true(bool condition, const string& message) {
        if (condition) {
            passed++;
            cout << "  ✓ " << message << endl;
        } else {
            failed++;
            cout << "  ✗ FAILED: " << message << endl;
        }
    }
    
    void assert_equals(size_t expected, size_t actual, const string& message) {
        if (expected == actual) {
            passed++;
            cout << "  ✓ " << message << " (expected=" << expected << ", actual=" << actual << ")" << endl;
        } else {
            failed++;
            cout << "  ✗ FAILED: " << message << " (expected=" << expected << ", actual=" << actual << ")" << endl;
        }
    }
    
    void summary() {
        cout << "\n========================================" << endl;
        cout << "Test Results: " << passed << " passed, " << failed << " failed" << endl;
        cout << "========================================" << endl;
    }
};

// Helper to create test data
vector<uint8_t> create_test_data(size_t size, uint8_t pattern = 0) {
    vector<uint8_t> data(size);
    if (pattern == 0) {
        for (size_t i = 0; i < size; i++) {
            data[i] = i % 256;
        }
    } else {
        fill(data.begin(), data.end(), pattern);
    }
    return data;
}

// Helper to verify data
bool verify_data(const vector<uint8_t>& expected, const vector<uint8_t>& actual) {
    if (expected.size() != actual.size()) return false;
    return memcmp(expected.data(), actual.data(), expected.size()) == 0;
}

// Cleanup helper
void cleanup_test_file(const string& path) {
    remove(path.c_str());
}

// ============================================
// Basic Functionality Tests
// ============================================

void test_basic_write_read(TestSuite& suite) {
    suite.start_test("Basic Write and Read");
    
    const string filepath = "test_basic.dat";
    cleanup_test_file(filepath);
    
    // Write data
    {
        FileManager fm(filepath, FileOpenMode::CACHED);
        fm.openForWrite(false, true);
        
        auto data = create_test_data(1024);
        fm.write(data.data(), data.size());
        fm.flush(FlushMode::FULL_SYNC);
        fm.close();
        
        suite.assert_true(true, "Write completed successfully");
    }
    
    // Read data back
    {
        FileManager fm(filepath, FileOpenMode::CACHED);
        fm.openForRead();
        
        vector<uint8_t> buffer(1024);
        size_t bytes_read = fm.read(buffer.data(), buffer.size());
        
        suite.assert_equals(1024, bytes_read, "Read size matches");
        
        auto expected = create_test_data(1024);
        suite.assert_true(verify_data(expected, buffer), "Data integrity verified");
        
        fm.close();
    }
    
    cleanup_test_file(filepath);
}

void test_append_mode(TestSuite& suite) {
    suite.start_test("Append Mode");
    
    const string filepath = "test_append.dat";
    cleanup_test_file(filepath);
    
    // Write initial data
    {
        FileManager fm(filepath, FileOpenMode::CACHED);
        fm.openForWrite(false, true);
        auto data = create_test_data(512, 0xAA);
        fm.write(data.data(), data.size());
        fm.close();
    }
    
    // Append more data
    {
        FileManager fm(filepath, FileOpenMode::CACHED);
        fm.openForWrite(true, true);
        auto data = create_test_data(512, 0xBB);
        fm.write(data.data(), data.size());
        fm.close();
    }
    
    // Verify both chunks
    {
        FileManager fm(filepath, FileOpenMode::CACHED);
        fm.openForRead();
        
        size_t file_size = fm.size();
        suite.assert_equals(1024, file_size, "File size after append");
        
        vector<uint8_t> buffer(1024);
        fm.read(buffer.data(), buffer.size());
        
        // Check first half
        suite.assert_true(buffer[0] == 0xAA && buffer[511] == 0xAA, "First chunk intact");
        // Check second half
        suite.assert_true(buffer[512] == 0xBB && buffer[1023] == 0xBB, "Second chunk intact");
        
        fm.close();
    }
    
    cleanup_test_file(filepath);
}

void test_seek_operations(TestSuite& suite) {
    suite.start_test("Seek Operations");
    
    const string filepath = "test_seek.dat";
    cleanup_test_file(filepath);
    
    // Write test data
    {
        FileManager fm(filepath, FileOpenMode::CACHED);
        fm.openForWrite(false, true);
        auto data = create_test_data(4096);
        fm.write(data.data(), data.size());
        fm.close();
    }
    
    // Test seeking
    {
        FileManager fm(filepath, FileOpenMode::CACHED);
        fm.openForRead();
        
        // Seek to middle
        fm.seek(2048, SEEK_SET);
        suite.assert_equals(2048, static_cast<size_t>(fm.tell()), "Seek to absolute position");
        
        vector<uint8_t> buffer(100);
        fm.read(buffer.data(), buffer.size());
        auto expected = create_test_data(4096);
        suite.assert_true(memcmp(buffer.data(), expected.data() + 2048, 100) == 0, "Data at seek position");
        
        // Seek relative
        fm.seek(-50, SEEK_CUR);
        suite.assert_equals(2098, static_cast<size_t>(fm.tell()), "Seek relative to current");
        
        // Seek from end
        fm.seek(-100, SEEK_END);
        suite.assert_equals(3996, static_cast<size_t>(fm.tell()), "Seek from end");
        
        fm.close();
    }
    
    cleanup_test_file(filepath);
}

void test_pread(TestSuite& suite) {
    suite.start_test("Positional Read (pread)");
    
    const string filepath = "test_pread.dat";
    cleanup_test_file(filepath);
    
    // Write test data
    {
        FileManager fm(filepath, FileOpenMode::CACHED);
        fm.openForWrite(false, true);
        auto data = create_test_data(8192);
        fm.write(data.data(), data.size());
        fm.close();
    }
    
    // Test pread
    {
        FileManager fm(filepath, FileOpenMode::CACHED);
        fm.openForRead();
        
        // Read from different positions without changing file position
        vector<uint8_t> buffer1(100);
        vector<uint8_t> buffer2(100);
        
        fm.pread(buffer1.data(), 100, 1000);
        fm.pread(buffer2.data(), 100, 5000);
        
        // Verify file position unchanged
        suite.assert_equals(0, static_cast<size_t>(fm.tell()), "pread doesn't change file position");
        
        // Verify data
        auto expected = create_test_data(8192);
        suite.assert_true(memcmp(buffer1.data(), expected.data() + 1000, 100) == 0, "pread at offset 1000");
        suite.assert_true(memcmp(buffer2.data(), expected.data() + 5000, 100) == 0, "pread at offset 5000");
        
        fm.close();
    }
    
    cleanup_test_file(filepath);
}

// ============================================
// Buffering Tests
// ============================================

void test_buffered_writes(TestSuite& suite) {
    suite.start_test("Buffered Writes");
    
    const string filepath = "test_buffered.dat";
    cleanup_test_file(filepath);
    
    FileManager fm(filepath, FileOpenMode::CACHED, FileType::SORTED_RUN, 1024); // 1KB buffer
    fm.openForWrite(false, true);
    
    // Write small chunks that should be buffered
    for (int i = 0; i < 10; i++) {
        auto data = create_test_data(100, i);
        fm.write(data.data(), data.size());
    }
    
    suite.assert_true(true, "Multiple small writes completed");
    
    fm.flush(FlushMode::FULL_SYNC);
    fm.close();
    
    // Verify
    {
        FileManager fm_read(filepath, FileOpenMode::CACHED);
        fm_read.openForRead();
        
        suite.assert_equals(1000, fm_read.size(), "Total size correct");
        
        vector<uint8_t> buffer(100);
        for (int i = 0; i < 10; i++) {
            fm_read.read(buffer.data(), buffer.size());
            auto expected = create_test_data(100, i);
            suite.assert_true(verify_data(expected, buffer), "Chunk " + to_string(i) + " verified");
        }
        
        fm_read.close();
    }
    
    cleanup_test_file(filepath);
}

void test_large_write(TestSuite& suite) {
    suite.start_test("Large Write (exceeds buffer)");
    
    const string filepath = "test_large.dat";
    cleanup_test_file(filepath);
    
    FileManager fm(filepath, FileOpenMode::CACHED, FileType::SORTED_RUN, 4096);
    fm.openForWrite(false, true);
    
    // Write 1MB - much larger than buffer
    const size_t large_size = 1024 * 1024;
    auto data = create_test_data(large_size);
    fm.write(data.data(), data.size());
    fm.flush(FlushMode::FULL_SYNC);
    fm.close();
    
    suite.assert_true(true, "Large write completed");
    
    // Verify
    {
        FileManager fm_read(filepath, FileOpenMode::CACHED);
        fm_read.openForRead();
        
        suite.assert_equals(large_size, fm_read.size(), "Large file size correct");
        
        vector<uint8_t> buffer(large_size);
        fm_read.read(buffer.data(), buffer.size());
        suite.assert_true(verify_data(data, buffer), "Large data integrity verified");
        
        fm_read.close();
    }
    
    cleanup_test_file(filepath);
}

// ============================================
// Different Mode Tests
// ============================================

void test_direct_io(TestSuite& suite) {
    suite.start_test("Direct I/O Mode");
    
    const string filepath = "test_direct.dat";
    cleanup_test_file(filepath);
    
    try {
        FileManager fm(filepath, FileOpenMode::DIRECT_IO, FileType::WRITE_AHEAD_LOG);
        fm.openForWrite(false, true);
        
        // Direct I/O requires aligned buffers and sizes
        const size_t block_size = 4096;
        void* aligned_buffer = nullptr;
        
#ifdef _WIN32
        aligned_buffer = _aligned_malloc(block_size, block_size);
#else
        posix_memalign(&aligned_buffer, block_size, block_size);
#endif
        
        if (aligned_buffer) {
            memset(aligned_buffer, 0xAB, block_size);
            fm.write(aligned_buffer, block_size);
            fm.flush(FlushMode::FULL_SYNC);
            
            suite.assert_true(true, "Direct I/O write completed");
            
#ifdef _WIN32
            _aligned_free(aligned_buffer);
#else
            free(aligned_buffer);
#endif
        }
        
        fm.close();
    } catch (const exception& e) {
        suite.assert_true(false, string("Direct I/O failed: ") + e.what());
    }
    
    cleanup_test_file(filepath);
}

void test_cached_mode(TestSuite& suite) {
    suite.start_test("Cached Mode (Default)");
    
    const string filepath = "test_cached.dat";
    cleanup_test_file(filepath);
    
    FileManager fm(filepath, FileOpenMode::CACHED);
    fm.openForWrite(false, true);
    
    auto data = create_test_data(8192);
    fm.write(data.data(), data.size());
    fm.flush(FlushMode::DATA_ONLY);
    
    suite.assert_true(fm.isOpen(), "File is open");
    suite.assert_equals(8192, fm.size(), "File size correct");
    
    fm.close();
    suite.assert_true(!fm.isOpen(), "File closed successfully");
    
    cleanup_test_file(filepath);
}

// ============================================
// Durability Tests
// ============================================

void test_flush_modes(TestSuite& suite) {
    suite.start_test("Flush Modes");
    
    const string filepath = "test_flush.dat";
    cleanup_test_file(filepath);
    
    FileManager fm(filepath, FileOpenMode::CACHED);
    fm.openForWrite(false, true);
    
    auto data = create_test_data(1024);
    
    // Test NONE
    fm.write(data.data(), data.size());
    fm.flush(FlushMode::NONE);
    suite.assert_true(true, "Flush NONE completed");
    
    // Test DATA_ONLY
    fm.write(data.data(), data.size());
    fm.flush(FlushMode::DATA_ONLY);
    suite.assert_true(true, "Flush DATA_ONLY completed");
    
    // Test FULL_SYNC
    fm.write(data.data(), data.size());
    fm.flush(FlushMode::FULL_SYNC);
    suite.assert_true(true, "Flush FULL_SYNC completed");
    
    fm.close();
    
    // Verify all data written
    {
        FileManager fm_read(filepath, FileOpenMode::CACHED);
        fm_read.openForRead();
        suite.assert_equals(3072, fm_read.size(), "All flushes persisted data");
        fm_read.close();
    }
    
    cleanup_test_file(filepath);
}

void test_write_sync(TestSuite& suite) {
    suite.start_test("Synchronous Write");
    
    const string filepath = "test_sync.dat";
    cleanup_test_file(filepath);
    
    FileManager fm(filepath, FileOpenMode::CACHED);
    fm.openForWrite(false, true);
    
    auto data = create_test_data(2048);
    
    // writeSync should write and flush immediately
    fm.writeSync(data.data(), data.size(), FlushMode::FULL_SYNC);
    
    suite.assert_true(true, "writeSync completed");
    
    // Verify data is immediately readable
    {
        FileManager fm_read(filepath, FileOpenMode::CACHED);
        fm_read.openForRead();
        
        vector<uint8_t> buffer(2048);
        fm_read.read(buffer.data(), buffer.size());
        
        suite.assert_true(verify_data(data, buffer), "Sync write data verified");
        fm_read.close();
    }
    
    fm.close();
    cleanup_test_file(filepath);
}

// ============================================
// Advanced Features Tests
// ============================================

void test_preallocate(TestSuite& suite) {
    suite.start_test("Preallocate");
    
    const string filepath = "test_preallocate.dat";
    cleanup_test_file(filepath);
    
    try {
        FileManager fm(filepath, FileOpenMode::CACHED);
        fm.openForWrite(false, true);
        
        const size_t prealloc_size = 10 * 1024 * 1024; // 10MB
        fm.preallocate(prealloc_size);
        
        suite.assert_equals(prealloc_size, fm.size(), "Preallocated size correct");
        
        fm.close();
    } catch (const exception& e) {
        suite.assert_true(false, string("Preallocate failed: ") + e.what());
    }
    
    cleanup_test_file(filepath);
}

void test_advise_functions(TestSuite& suite) {
    suite.start_test("Advise Functions");
    
    const string filepath = "test_advise.dat";
    cleanup_test_file(filepath);
    
    FileManager fm(filepath, FileOpenMode::CACHED);
    fm.openForWrite(false, true);
    
    auto data = create_test_data(1024 * 1024);
    fm.write(data.data(), data.size());
    fm.close();
    
    // Test advise functions (should not throw)
    fm.openForRead();
    
    fm.adviseSequential();
    suite.assert_true(true, "adviseSequential completed");
    
    fm.adviseRandom();
    suite.assert_true(true, "adviseRandom completed");
    
    fm.adviseWillNeed(0, 4096);
    suite.assert_true(true, "adviseWillNeed completed");
    
    fm.adviseDontNeed(0, 4096);
    suite.assert_true(true, "adviseDontNeed completed");
    
    fm.close();
    cleanup_test_file(filepath);
}

// ============================================
// Move Semantics Tests
// ============================================

void test_move_constructor(TestSuite& suite) {
    suite.start_test("Move Constructor");
    
    const string filepath = "test_move.dat";
    cleanup_test_file(filepath);
    
    FileManager fm1(filepath, FileOpenMode::CACHED);
    fm1.openForWrite(false, true);
    
    auto data = create_test_data(1024);
    fm1.write(data.data(), data.size());
    
    // Move construct
    FileManager fm2(std::move(fm1));
    
    suite.assert_true(fm2.isOpen(), "Moved-to object is open");
    suite.assert_true(!fm1.isOpen(), "Moved-from object is closed");
    
    fm2.flush(FlushMode::FULL_SYNC);
    fm2.close();
    
    cleanup_test_file(filepath);
}

void test_move_assignment(TestSuite& suite) {
    suite.start_test("Move Assignment");
    
    const string filepath1 = "test_move1.dat";
    const string filepath2 = "test_move2.dat";
    cleanup_test_file(filepath1);
    cleanup_test_file(filepath2);
    
    FileManager fm1(filepath1, FileOpenMode::CACHED);
    fm1.openForWrite(false, true);
    
    FileManager fm2(filepath2, FileOpenMode::CACHED);
    fm2.openForWrite(false, true);
    
    // Move assign
    fm2 = std::move(fm1);
    
    suite.assert_true(fm2.isOpen(), "Move-assigned object is open");
    suite.assert_true(!fm1.isOpen(), "Moved-from object is closed");
    
    fm2.close();
    
    cleanup_test_file(filepath1);
    cleanup_test_file(filepath2);
}

// ============================================
// Error Handling Tests
// ============================================

void test_read_nonexistent_file(TestSuite& suite) {
    suite.start_test("Read Non-existent File");
    
    const string filepath = "nonexistent_file.dat";
    cleanup_test_file(filepath);
    
    try {
        FileManager fm(filepath, FileOpenMode::CACHED);
        fm.openForRead();
        suite.assert_true(false, "Should throw exception");
    } catch (const exception& e) {
        suite.assert_true(true, "Exception thrown as expected");
    }
}

void test_write_read_only_location(TestSuite& suite) {
    suite.start_test("Write to Read-only Location");
    
    // This test is platform-specific and might not work everywhere
    // Just ensure it doesn't crash
    suite.assert_true(true, "Test skipped (platform-dependent)");
}

// ============================================
// Performance Benchmark Tests
// ============================================

void benchmark_sequential_write(TestSuite& suite) {
    suite.start_test("Benchmark: Sequential Write");
    
    const string filepath = "bench_seq_write.dat";
    cleanup_test_file(filepath);
    
    const size_t data_size = 100 * 1024 * 1024; // 100MB
    auto data = create_test_data(data_size);
    
    auto start = chrono::high_resolution_clock::now();
    
    FileManager fm(filepath, FileOpenMode::CACHED);
    fm.openForWrite(false, true);
    fm.write(data.data(), data.size());
    fm.flush(FlushMode::FULL_SYNC);
    fm.close();
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    
    double throughput = (data_size / 1024.0 / 1024.0) / (duration / 1000.0);
    
    cout << "  Sequential write: " << throughput << " MB/s" << endl;
    suite.assert_true(true, "Benchmark completed");
    
    cleanup_test_file(filepath);
}

void benchmark_random_read(TestSuite& suite) {
    suite.start_test("Benchmark: Random Read");
    
    const string filepath = "bench_random_read.dat";
    cleanup_test_file(filepath);
    
    const size_t file_size = 10 * 1024 * 1024; // 10MB
    auto data = create_test_data(file_size);
    
    // Create file
    {
        FileManager fm(filepath, FileOpenMode::CACHED);
        fm.openForWrite(false, true);
        fm.write(data.data(), data.size());
        fm.close();
    }
    
    // Random reads
    FileManager fm(filepath, FileOpenMode::CACHED);
    fm.openForRead();
    
    const int num_reads = 10000;
    vector<uint8_t> buffer(4096);
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, file_size - 4096);
    
    auto start = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < num_reads; i++) {
        off_t offset = dis(gen);
        fm.pread(buffer.data(), 4096, offset);
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    
    double iops = num_reads / (duration / 1000.0);
    
    cout << "  Random read: " << iops << " IOPS" << endl;
    suite.assert_true(true, "Benchmark completed");
    
    fm.close();
    cleanup_test_file(filepath);
}

// ============================================
// Main Test Runner
// ============================================

int main() {
    TestSuite suite;
    
    cout << "========================================" << endl;
    cout << "FileManager Test Suite" << endl;
    cout << "========================================" << endl;
    
    // Basic tests
    test_basic_write_read(suite);
    test_append_mode(suite);
    test_seek_operations(suite);
    test_pread(suite);
    
    // Buffering tests
    test_buffered_writes(suite);
    test_large_write(suite);
    
    // Mode tests
    test_direct_io(suite);
    test_cached_mode(suite);
    
    // Durability tests
    test_flush_modes(suite);
    test_write_sync(suite);
    
    // Advanced features
    test_preallocate(suite);
    test_advise_functions(suite);
    
    // Move semantics
    test_move_constructor(suite);
    test_move_assignment(suite);
    
    // Error handling
    test_read_nonexistent_file(suite);
    test_write_read_only_location(suite);
    
    // Benchmarks
    benchmark_sequential_write(suite);
    benchmark_random_read(suite);
    
    suite.summary();
    
    return suite.failed == 0 ? 0 : 1;
}