class Q {
    void A1() {
        System.out.println("In A1");
    }

    void B1() {
        System.out.println("In B1");
    }

    void A2() {
        System.out.println("In A2");
    }

    void B2() {
        System.out.println("In B2");
    }

    boolean l1 = false;
    boolean l2 = false;
    boolean l3 = false;

    synchronized void Thread1() {
        A1();
        l1 = true;
        notify();
        while (!l2) {
            try {
                wait();
            } catch (InterruptedException e) {
                System.out.println("Interrupted exception caught\n");
            }
        }
        A2();
        l3 = true;
        notify();
    }

    synchronized void Thread2() {
        while (!l1) {
            try {
                wait();
            } catch (InterruptedException e) {
                System.out.println("Interrupted exception caught\n");
            }
        }
        B1();
        l2 = true;
        notify();
        while (!l3) {
            try {
                wait();
            } catch (InterruptedException e) {
                System.out.println("Interrupted exception caught\n");
            }
        }
        B2();
    }
}

class Sync implements Runnable {
    Sync(Q q, int tid) {
        this.q = q;
        this.tid = tid;
        thr = new Thread(this);
        thr.start();
    }

    public void run() {
        if (tid == 1) {
            q.Thread1();
        }
        if (tid == 2) {
            q.Thread2();
        }
    }

    Q q;
    int tid;
    Thread thr;
}

class PrintA1B1A2B2 {
    public static void main(String args[]) {
        Q q = new Q();
        new Sync(q, 1);
        new Sync(q, 2);
    }
}
