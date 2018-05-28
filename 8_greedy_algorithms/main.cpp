#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Job{
    Job() {}
    vector<int> length;
    vector<int> weight;
};

void read_file(const char* input_file_name, Job& jobs_data)
{
    ifstream data_file;
    data_file.open(input_file_name);

    string input_file_length;
    int number_of_lines = 0;
    getline(data_file, input_file_length);
    number_of_lines = atoi( input_file_length.c_str() );

    cout << "Number of input lines " << number_of_lines << endl;

    string job_weight_line;
    while ( getline(data_file, job_weight_line) )
    {
        if (job_weight_line != "")
        {
            stringstream line(job_weight_line);
            int weight, length;
            line >> weight;
            line >> length;

            jobs_data.weight.push_back(weight);
            jobs_data.length.push_back(length);
        }
    }
}


int main(int argc, char *argv[])
{
    char intput_file_name[] = "jobs.txt";
    Job job;
    read_file(intput_file_name, job);

//    for (int i = 0; i < job.length.size(); ++i)
//        cout << job.weight[i] << " " << job.length[i] << endl;

    cout << "Length: " << job.length.size() << endl;



    return 0;
}
