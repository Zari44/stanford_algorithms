#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Job{
    int length, weight;
    bool operator < (const Job& job) const
    {
        int diff = weight - length;
        int job_diff = job.weight - job.length;
        if (diff == job_diff)
            return weight > job.weight;
        return (diff > job_diff);
    }
};

void read_file(const char* input_file_name, vector<Job>& jobs_data)
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
            Job job;
            line >> job.weight;
            line >> job.length;

            jobs_data.push_back(job);
        }
    }
}

unsigned long calculate_sum_of_weighted_completion_time(const vector<Job>& jobs)
{
    unsigned long sum = 0;
    unsigned long completion_time = 0;
    for (vector<Job>::const_iterator job = jobs.begin(); job != jobs.end(); ++job)
    {
        completion_time += job->length;
        sum += completion_time * job->weight;
    }

    return sum;
}


int main()
{
    char intput_file_name[] = "jobs.txt";
    vector<Job> jobs;
    read_file(intput_file_name, jobs);

    sort(jobs.begin(), jobs.end());

    for (int i = 0; i < jobs.size()/10; ++i)
        cout << jobs[i].weight << " " << jobs[i].length << endl;

//    cout << "Length: " << jobs.size() << endl;

    cout << "Sum of weighted completion times: " << calculate_sum_of_weighted_completion_time(jobs) << endl;


    return 0;
}
