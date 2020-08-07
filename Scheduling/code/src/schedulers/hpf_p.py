from utils import generate_jobs

# TODO: calculate wait time
#       run for 100 procs
#       replicate experiment as per requirements

def hpf(jobs, quanta):
    # we'll track the index so we can remove the
    # job later
    i = 0
    hp_job = jobs[0]
    for job in jobs:
        if job['time_slot']:
            hp_i = i
            break

        if job['priority'] > hp_job['priority']:
            hp_i = i
        
        i+=1

    jobs[hp_i]['remaining_service_time'] -= 1
    jobs[hp_i]['time_slot'].append(quanta)

    if jobs[hp_i]['remaining_service_time'] == 0:
        return jobs[hp_i]
    else:
        return None


def os(jobs, scheduler):
    quanta = 0
    waiting_jobs = jobs
    running_jobs = []
    completed_jobs = []
    while True:
        if quanta > 99 and running_jobs == []:
            break
        quanta +=1
        for job in waiting_jobs:
            if job['arrival_time'] == quanta:
                running_jobs.append(job)
                waiting_jobs.remove(job)

        # just skip if no job to process
        if running_jobs == []:
            continue

        job_to_move = scheduler(running_jobs)
        if job_to_move is not None:
            completed_jobs.append(job_to_move)
            running_jobs.remove(job_to_move)
       
    return completed_jobs

jobs = generate_jobs(10)

# print initial jobs
for job in jobs:
    print(job)
    
completed_jobs = os(jobs, hpf)

# check results
for job in completed_jobs:
    print(job)
