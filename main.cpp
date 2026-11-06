#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <memory>
using namespace std;

class EWaste {
protected: int id; string name; double kg;
public:
    EWaste(int i, string n, double w) : id(i), name(n), kg(w) {}
    virtual ~EWaste() {}
    virtual string type() const = 0;
    virtual double rate() const = 0;               // recyclable fraction
    bool recyclable() const { return rate() > 0; }
    double recovered() const { return kg * rate(); }
    double weight() const { return kg; }
    void show() const {
        cout << id << " " << name << " [" << type() << "] " << kg << " kg - "
             << (recyclable() ? "Recyclable" : "Non-recyclable") << "\n";
    }
    string record() const { return type() + "," + to_string(id) + "," + name + "," + to_string(kg); }
};
class Computer : public EWaste { public: using EWaste::EWaste;
    string type() const override { return "Computer"; }  double rate() const override { return 0.85; } };
class Mobile : public EWaste { public: using EWaste::EWaste;
    string type() const override { return "Mobile"; }    double rate() const override { return 0.80; } };
class Battery : public EWaste { public: using EWaste::EWaste;
    string type() const override { return "Battery"; }   double rate() const override { return 0.60; } };
class CRTMonitor : public EWaste { public: using EWaste::EWaste;
    string type() const override { return "CRTMonitor"; } double rate() const override { return 0.0; } };

class Manager {
    vector<unique_ptr<EWaste>> v;
public:
    void add(const string& t, int id, const string& n, double w) {
        if (t == "Computer")        v.push_back(unique_ptr<EWaste>(new Computer(id, n, w)));
        else if (t == "Mobile")     v.push_back(unique_ptr<EWaste>(new Mobile(id, n, w)));
        else if (t == "Battery")    v.push_back(unique_ptr<EWaste>(new Battery(id, n, w)));
        else if (t == "CRTMonitor") v.push_back(unique_ptr<EWaste>(new CRTMonitor(id, n, w)));
    }
    void save(const string& f) const { ofstream o(f); for (auto& e : v) o << e->record() << "\n"; }
    void load(const string& f) {
        ifstream in(f); string l, t, i, n, w; v.clear();
        while (getline(in, l)) {
            stringstream s(l);
            getline(s, t, ','); getline(s, i, ','); getline(s, n, ','); getline(s, w, ',');
            add(t, stoi(i), n, stod(w));
        }
    }
    void report() const {
        map<string, double> cat; double tot = 0, rec = 0; int r = 0, nr = 0;
        for (auto& e : v) {
            e->show();
            cat[e->type()] += e->weight(); tot += e->weight(); rec += e->recovered();
            e->recyclable() ? r++ : nr++;
        }
        cout << "\n--- Summary ---\n";
        for (auto& c : cat) cout << c.first << ": " << c.second << " kg\n";
        cout << "Recyclable items: " << r << ", Non-recyclable: " << nr << "\n"
             << "Total weight: " << tot << " kg\nRecoverable weight: " << rec << " kg\n"
             << "Recycling rate: " << rec / tot * 100 << " %\n";
    }
};

int main() {
    Manager m;
    m.add("Computer", 101, "Desktop", 9.5);   m.add("Mobile", 102, "Smartphone", 0.18);
    m.add("Battery", 103, "LaptopBattery", 0.45); m.add("CRTMonitor", 104, "CRT17in", 14);
    m.add("Computer", 105, "Laptop", 2.3);    m.add("Mobile", 106, "FeaturePhone", 0.12);
    m.save("ewaste.txt");
    Manager n; n.load("ewaste.txt");           
    n.report();
}