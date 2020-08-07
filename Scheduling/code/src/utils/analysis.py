def analyze_results(jobs, stats_file_name):

    # Compute Gant Chart
    gant_chart_index = 0
    final_job_time_slot = jobs[len(jobs)-1]['time_slot']
    gant_chart_size = final_job_time_slot[len(final_job_time_slot) - 1]
    gant_chart = [-1] * (gant_chart_size +1)
    # print("Gant chart size is: ", gant_chart_size)
    for job in jobs:
        time_slots = job['time_slot']
        for i in time_slots:
            # print(i)
            gant_chart[i] = job['job_id']

    wait_time_all_jobs = 0
    turnaround_time_all_jobs = 0
    response_time_all_jobs = 0
    for job in jobs:
        wait_time_all_jobs += job['wait_time']
        turnaround_time_all_jobs += job['turnaround_time']
        response_time_all_jobs += job['response_time']
    wait_time_avg = wait_time_all_jobs / len(jobs)
    turnaround_time_avg = turnaround_time_all_jobs / len(jobs)
    response_time_avg = response_time_all_jobs / len(jobs)

    jobs_completed = len(jobs)
    quanta_utilized = len(gant_chart)
    final_throughput = len(jobs)/len(gant_chart)
    
    stats_file = open(stats_file_name, 'a')
    stats_file.write("Gantt Chart:\n")
    stats_file.write(str(gant_chart)+ '\n')
    # print()
    stats_file.write("------- STATISTICS -------\n")
    stats_file.write("Wait time average: "+ str(wait_time_avg) + '\n')
    stats_file.write("Turnaround time average: "+ str(turnaround_time_avg) + '\n')
    stats_file.write("Average Response Time: "+ str(response_time_avg) + '\n')
    stats_file.write("Total Jobs Completed: "+ str(jobs_completed) + '\n')
    stats_file.write("Total Quanta Utilized: "+ str(quanta_utilized) + '\n')
    stats_file.write("Throughput: "+ str(final_throughput)+" jobs/sec" + '\n')
    
    stats_file.close()
    return gant_chart, wait_time_avg, turnaround_time_avg, response_time_avg,\
    jobs_completed, final_throughput
