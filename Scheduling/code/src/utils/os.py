import utils.keys

def os(jobs, algorithm):
    quanta = 0
    job_count = len(jobs)
    waiting_jobs = jobs
    running_jobs =[]
    completed_jobs = []
    delete_jobs = []
    
    while True:
        if quanta > 99 and running_jobs == []:
            break

        wait_jobs_len = len(waiting_jobs)
        # for i in range(0, wait_jobs_len):
        i = 0
        while i < wait_jobs_len:
            if waiting_jobs[i]['arrival_time'] == quanta:
                running_jobs.append(waiting_jobs[i])
                waiting_jobs.remove(waiting_jobs[i])
                utils.keys.job_added = 1
                wait_jobs_len -=1
            else:
                i+=1
        
        #remove jobs not scheduled until quanta 99
        if quanta == 100:
            for index,job in enumerate(running_jobs):
                if job['time_slot'] == []:
                    delete_jobs.append(index)
            #type casting to tuple because "in" is O(1) for tuples
            delete_jobs = tuple(delete_jobs)
            running_jobs = [job for index,job in enumerate(running_jobs) if index not in delete_jobs]
       
        # implement the algorithm if running_jobs is not empty
        if running_jobs:
            job_to_be_removed = algorithm(running_jobs, quanta)
            if job_to_be_removed:
                completed_jobs.append(job_to_be_removed)
                running_jobs.remove(job_to_be_removed)
        else:
            utils.keys.idle = 1

        quanta +=1
    return completed_jobs

