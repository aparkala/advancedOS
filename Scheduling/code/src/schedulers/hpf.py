# TODO: calculate wait time
#       run for 100 procs
#       replicate experiment as per requirements

def hpf(jobs, quanta):
    # we'll track the index so we can remove the
    # job later
    hp_i = 0
    i = 0
    hp_job = jobs[0]
    for job in jobs:
        if job['priority'] > hp_job['priority']:
            hp_i = i
        
        i+=1

    jobs[hp_i]['remaining_service_time'] -= 1
    jobs[hp_i]['time_slot'].append(quanta)
    
    if jobs[hp_i]['remaining_service_time'] == 0:
        jobs[hp_i]['turnaround_time'] = quanta - jobs[hp_i]['arrival_time']
        jobs[hp_i]['wait_time'] = jobs[hp_i]['turnaround_time'] - jobs[hp_i]['service_time']

        return jobs[hp_i]
    else:
        return None
