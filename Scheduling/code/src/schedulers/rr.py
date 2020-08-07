import utils.keys

def rr(running_jobs, quanta):

    # reset rr keys if cpu was idle in previous quanta
    if utils.keys.idle:
        utils.keys.idle = 0
        utils.keys.job_finished = 0
        
    # find the job to be scheduled
    # if job finished running in the previous quanta
    if utils.keys.job_finished:
        utils.keys.job_finished = 0
        
        # if the finished job was first in the queue and a new job was added to the queue in this quanta
        if utils.keys.last_job == 0 and utils.keys.job_added:
            utils.keys.last_job = len(running_jobs) - 1
        else:
            utils.keys.last_job -= 1
    
    utils.keys.job_added = 0
    previous = utils.keys.last_job
    current = (previous + 1) % len(running_jobs)
    
    #set response time if job is run for the first time
    if running_jobs[current]['response_time'] == -1:
        running_jobs[current]['response_time'] = quanta - running_jobs[current]['arrival_time']
        
    #run the current job, append quanta to time_slot and set last_job = 1
    running_jobs[current]['remaining_service_time'] -= 1
    running_jobs[current]['time_slot'].append(quanta)
    utils.keys.last_job = current
        
    #if job has completed execution
    if running_jobs[current]['remaining_service_time'] == 0:
        running_jobs[current]['turnaround_time'] = quanta - running_jobs[current]['arrival_time'] + 1
        running_jobs[current]['wait_time'] = running_jobs[current]['turnaround_time'] - running_jobs[current]['service_time']
        utils.keys.job_finished = 1
        return running_jobs[current]
    else:
        return None










#def round_robin(jobs):
#    print("Entered cpu\n") #debugging
#    gantt_chart = []
#    quanta = 0
#    waiting_jobs = jobs
#    running_job =[]
#    completed_jobs = []
#    previous = -1
#
#    while True:
#        #print("start of while\n") #debugging
#        if quanta > 99 and running_job == []:
#            break
#        #print(quanta) debugging
#
#        #defining two more variables: time_slice_start and time_slice_end
#        time_slice_start = quanta
#        time_slice_end = quanta + 1
#
#        for job in waiting_jobs:
#            #print("searching jobs\n") #debugging
#            if job['arrival_time'] == time_slice_start:
#                #print("found job: \n",job,"\n") #debugging
#                running_job.append(job)
#                waiting_jobs.remove(job)
#
#        # algo (note: consider 1 time slice to be 1 second for ease of understanding)
#        if len(running_job) >= 1: #when the first job is ready
#            # debugging
#            #print("running job\n")
#            # print("previous job: ",previous%len(running_job),"len :",len(running_job), " : ",running_job[previous%len(running_job)], "\n")
#
#            # previous holds the index of the job that last ran on the CPU
#            current = previous + 1
#
#
#            # debugging
#            #print("current job: ", current%len(running_job),"len :",len(running_job), " : ",running_job[current%len(running_job)], "\n")
#
#            #when the previous job that ran is the last job in the queue, it is reset
#            current = current % len(running_job)
#            current_job = running_job[current]
#
#            # if there exists a job that has not gotten cpu even once until quanta = 99, dont schedule the job
#            if current_job['response_time'] == -1 and quanta > 99 :
#                running_job.remove(current_job)
#                current -= 1
#                continue
#
#            #set response time if job is run for the first time
#            if current_job['response_time'] == -1:
#                current_job['response_time'] = time_slice_start - current_job['arrival_time']
#
#            #run the current job, append time slice and append job_id to cpu gantt chart
#            current_job['remaining_service_time'] -= 1
#            current_job['time_slot'].append(time_slice_start)
#            gantt_chart.append(current_job['job_id'])
#
#            #if job has completed execution
#            if current_job['remaining_service_time'] == 0:
#                # compute turnaround and wait time
#                current_job['turnaround_time'] = time_slice_end - current_job['arrival_time']#
#                current_job['wait_time'] = current_job['turnaround_time'] - current_job['service_time']
#
#                # append job to completed jobs
#                completed_jobs.append(current_job)
#                running_job.remove(current_job)
#
#                #when we remove the completed job from running_job, the next job that has to run would have the same index as the completed job
#                current -= 1
#            previous = current
#        else: # when cpu is idle, append -1 to gantt chart
#            gantt_chart.append(-1)
#        #print("end of while\n") #debugging
#        quanta +=1
#        continue
#
#    #computing avg response, wait and turnaround times
#    print("printing results")
#
#    print_all_jobs_properties(completed_jobs)
#
#    wait_time_all_jobs = 0
#    turnaround_time_all_jobs = 0
#    response_time_all_jobs = 0
#    for job in completed_jobs:
#        wait_time_all_jobs += job['wait_time']
#        turnaround_time_all_jobs += job['turnaround_time']
#        response_time_all_jobs += job['response_time']
#    wait_time_avg = wait_time_all_jobs / len(completed_jobs)
#    turnaround_time_avg = turnaround_time_all_jobs / len(completed_jobs)
#    response_time_avg = response_time_all_jobs / len(completed_jobs)
#
#    print("Gantt Chart:")
#    print(gantt_chart)
#    print()
#    print("------- STATISTICS -------")
#    print("Wait time average: ", wait_time_avg)
#    print("Turnaround time average: ", turnaround_time_avg)
#    print("Average Response Time: ", response_time_avg)
# #   print("Total Jobs Completed: ", len(completed_jobs))
#    print("Total Quanta Utilised: ", len(gantt_chart))
#    print("Throughput: ", len(completed_jobs)/len(gantt_chart),"jobs/sec")


#random.seed(77)
#jobs = generate_jobs(10)
#round_robin(jobs)
