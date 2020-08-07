import random
from datetime import datetime
from operator import itemgetter

def fcfs(running_jobs, quanta):
    for job in running_jobs:
        if not job['time_slot']:
            job['wait_time'] = quanta - job['arrival_time']
            job['response_time'] = job['wait_time']
        job['remaining_service_time'] -=1
        job['time_slot'].append(quanta)

        if job['remaining_service_time'] == 0:
            job['turnaround_time'] = quanta - job['arrival_time'] +1
            return job
        else:
            return None

# jobs = generate_jobs(30)
# print("JOBS: ")
# print_some_jobs_properties(jobs)

# completed_jobs = first_come_first_serve(jobs)

# analyze_results(completed_jobs, 'first_come_first_serve_result.txt')
# def first_come_first_serve():
#     # Generate Jobs
#     job_count = 5
#     jobs = generate_jobs(job_count)
#     completed_jobs = []

#     # print them all out for debugging
#     print("     FIRST COME FIRST SERVE")

#     # Run them...
#     # First come first serve requires ordering them in terms of runtime
#     jobs = sorted(jobs, key=itemgetter('arrival_time'))

#     # print again for debuggin purposes
#     print("     Jobs in arrival time order:")
#     print_all_jobs_properties(jobs)

#     print("Ready to start running jobs...")

#     # Now run the jobs in a time slice....
#     time_slice = -1
#     wait_time = []
#     turnaround_time = []

#     for job in jobs:
#         while True:
#             # increment time slice for next itteration
#             time_slice +=1
#             print(job['job_id'], end=" ")

#             if job['wait_time'] == -1:
#                 job['wait_time'] = time_slice
#                 wait_time.append(time_slice)
            
#             # Subtract 1 from service time
#             job['service_time'] -=1

#             # record current time slice
#             job['time_slot'].append(time_slice)

#             # If we finshed running the job, remove it frome jobs queue
#             if job['service_time'] == 0:
#                 completed_jobs.append(job)
#                 turnaround_time.append(time_slice)
#                 # If you want to remove jobs.....
#                 # jobs.remove(job)

#                 break


#     # Compute required time results
#     print()
#     print_all_jobs_properties(completed_jobs)
#     wait_time_avg = sum(wait_time) / job_count
#     turnaround_time_avg = sum(turnaround_time) / job_count
#     average_response_time = sum(wait_time) / job_count
#     print("Wait time average: ", wait_time_avg)
#     print("Turnaround time average: ", turnaround_time_avg)
#     print("Average Response Time (Same as Wait time): ", average_response_time)

#     # print(jobs)

# jobs = generate_jobs(4)
# first_come_first_serve()
