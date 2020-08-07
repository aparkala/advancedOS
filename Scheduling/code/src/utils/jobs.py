import random
from datetime import datetime
from operator import itemgetter

random.seed(77)

#       generate_jobs()
#
# Generates "job_count" number of jobs with the following properties:
#    1) Arrival time
#    2) Service time
#    3) Priority
#
# @param: job_count - int - number of jobs we want to generate
#
# @return: list_of_all_jobs - list - of dictionarys - list of all jobs and their
#           properties. Each property is defined in each index of the list.
#

def generate_jobs(job_count):
    jobs = []

    for i in range(0, job_count):
        job_properties = {
            'job_id': 0,
            'arrival_time': 0,
            'service_time': 0,
            'priority': 0,
            'time_slot': [],
            'wait_time': 0,
            'remaining_service_time': 0,
            'response_time': -1
        }

        job_properties['job_id'] = i

        # Random number from [0, 99]   (inclusive)
        job_properties['arrival_time'] = random.randint(0, 99)
        job_properties['service_time'] = job_properties['remaining_service_time'] = random.randint(1, 10)
        job_properties['priority'] = random.randint(0, 4)

        jobs.append(job_properties) 
    jobs = sorted(jobs, key=itemgetter('arrival_time', 'priority'))
    return jobs

#      print_all_jobs_properties()
#
# Prints all jobs and thier properties
#
# @param: jobs - list of dictionaries - list of jobs and their properties
def print_all_jobs_properties(jobs):
    for job in jobs:
        print(job)
    print()


def print_some_jobs_properties(jobs):
    for job in jobs:
        print("Job iD: ",job['job_id'], ",", "Arrival time ",job['arrival_time'], ",", "Priority ",job['priority'],", Time Slot", job['time_slot'], ", Wait time: ",job['wait_time'], ", Service time ", job['service_time'])
    print()

