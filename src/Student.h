#include <bits/stdc++.h>
#include <string>
#include <vector>

struct Student {
   private:
    std::string fname;
    std::string sname;
    std::vector<int> hw;
    int exam;

   public:
    Student(std::string sname, std::string fname, std::vector<int> hw,
            int exam) {
        this->fname = fname;
        this->sname = sname;
        this->hw = hw;
        this->exam = exam;
    }

    std::string getFName() { return fname; }

    std::string getSName() { return sname; }

    std::vector<int> getHw() { return hw; }

    int getExam() { return exam; }

    double getAverage() {
        int sum = 0;
        for (int i = 0; i < hw.size(); i++) sum += hw[i];
        double hwAverage;
        if (hw.size() > 0) hwAverage = (double)sum / hw.size();

        return 0.4 * hwAverage + 0.6 * exam;
    }

    double getMedian() {
        std::sort(hw.begin(), hw.end());
        if (hw.size() % 2 == 0) {
            return (double)(hw[(hw.size() - 1) / 2 + 1] +
                            hw[(hw.size() - 1) / 2]) /
                   2;
        } else
            return (double)hw[(hw.size() - 1) / 2];
    }
};