#include "../header.h"

class MergeContacts {
    struct Contact {
        string id;
        list<string> emails;

        string to_string() {
            stringstream ss;
            ss << "{";
            ss << id << ":";
            ss << "[";
            for (auto& email : emails) ss << email << ",";
            ss << "]";
            ss << "}";

            return ss.str();
        }
    };

   public:
    static void test() {
        list<Contact> contacts = {
            {"1", {"email11", "email12", "email13"}},
            {"2", {"email21", "email22", "email23"}},
            {"3", {"email31", "email12", "email23"}},
        };

        MergeContacts obj;
        auto res = obj.mergeContacts(contacts);
        for (auto contact : res) {
            cout << contact.to_string() << endl;
        }
    }

    list<Contact> mergeContacts(list<Contact>& contacts) {
        unordered_map<string, unordered_set<string>> contactIdToEmailsMapping;
        unordered_map<string, unordered_set<string>> emailToIdMapping;
        for (auto& contact : contacts) {
            for (auto email : contact.emails) {
                emailToIdMapping[email].insert(contact.id);
                contactIdToEmailsMapping[contact.id].insert(email);
            }
        }

        unordered_map<string, unordered_set<string>> newContactIdToEmailsMapping;
        for (auto& contact : contacts) {
            for (auto& email : contact.emails) {
                auto contactIds = emailToIdMapping[email];
                addToMerge(newContactIdToEmailsMapping, contactIdToEmailsMapping, contactIds);
            }
        }

        list<Contact> mergedContacts;
        for (auto& contact : newContactIdToEmailsMapping) {
            std::list<string> list(contact.second.begin(), contact.second.end());
            mergedContacts.push_back({contact.first, list});
        }

        return mergedContacts;
    }

    void addToMerge(unordered_map<string, unordered_set<string>>& newContactIdToEmailsMapping,
                    unordered_map<string, unordered_set<string>>& contactIdToEmailsMapping,
                    unordered_set<string> contactIds) {
        for (auto contactId : contactIds) {
            newContactIdToEmailsMapping[contactId].insert(contactIdToEmailsMapping[contactId].begin(), contactIdToEmailsMapping[contactId].end());
        }
    }
};