from schedulers.fcfs import fcfs 
from schedulers.rr import rr
from schedulers.sjf import sjf
from schedulers.hpf import hpf
import copy
#from schedulers.srt import srt

from utils.analysis import analyze_results
from utils.jobs import generate_jobs
from utils.os import os

NUM_JOBS = 100

jobs = generate_jobs(NUM_JOBS)
jobs_1 = copy.deepcopy(jobs)
jobs_2 = copy.deepcopy(jobs)
jobs_3 = copy.deepcopy(jobs)

results_fcsf    = os(jobs, fcfs)
results_sjf     = os(jobs_1, sjf)
results_rr      = os(jobs_2, rr)
results_hpf     = os(jobs_3, hpf)


analyze_results(results_fcsf,   '../data/results_fcsf.txt')
analyze_results(results_rr,     '../data/results_rr.txt')
analyze_results(results_sjf,    '../data/results_sjf.txt')
analyze_results(results_hpf,    '../data/results_hpf.txt')
