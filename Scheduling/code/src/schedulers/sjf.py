# import time
import random
from datetime import datetime
from operator import itemgetter

# Pick a seed at datetime.now(), but for testing use a static number like 42
# random.seed(datetime.now())
random.seed(0)


def sjf(running_job, quanta):
    current_job = running_job[0]
    current_job['remaining_service_time']-=1
    current_job['time_slot'].append(quanta)

    if current_job['remaining_service_time'] <= 0:
        #TODO: Handle jobs after 99 quanta
        # if quanta <= 99:
            # completed_jobs.append(running_job[0])
            running_job[0]['response_time'] = running_job[0]['wait_time']
            running_job[0]['turnaround_time'] = quanta - running_job[0]['arrival_time']
            return running_job[0]
    else:
        del running_job[0]
        running_job.sort(key=itemgetter('service_time'))
        current_job['wait_time'] = quanta - current_job['arrival_time']
        running_job.insert(0,current_job)
        return None


def test(running_job):
    running_job.sort(key=itemgetter('service_time'))



