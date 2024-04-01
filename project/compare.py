import time
import os
import subprocess
import pandas as pd
import atexit
os.chdir(os.path.dirname(__file__))

timestamp = time.strftime("%Y%m%d-%H%M%S")
is_end = False
def exit_handler():
    global is_end, is_macos
    if not is_end:
        print('Experiment is interrupted.')
        cmd = f'rm -rf exp/{timestamp}' if is_macos else f'rmdir /s /q exp\\{timestamp}'
        os.system(cmd)
atexit.register(exit_handler)

# check if macos or window
is_macos = os.name == 'posix'
print(f'Running on {"macOS" if is_macos else "Windows"}')

has_baseline = os.path.exists('baseline.csv')

MAX_MINUTE = 3
RUN_ITER = 3
SOURCE_FILE = 'helloworld.cpp'
TARGET_FILE = 'helloworld.out' if is_macos else 'helloworld.exe'

# compile helloworld.cpp
print('Compiling helloworld.cpp...')
cmd = './com_a_run.sh' if is_macos else 'com_a_run.bat'
os.system(cmd)

# create output folder
os.makedirs(f"exp/{timestamp}", exist_ok=True)
os.makedirs(f"exp/{timestamp}/output", exist_ok=True)

run_list = {
    'small grid' : 'grid-6-7',
    'medium grid' : 'grid-25-40',
    'large grid' : 'grid-100-180',

    'small random' : 'rand-5-7',
    'medium random' : 'rand-25-50',
    'large random' : 'rand-80-350',

    'small tree' : 'tree-5-4',
    'medium tree' : 'tree-25-24',
    'large tree' : 'tree-100-99',
}

df = pd.DataFrame(columns=['file', 'time(s)'],
                  index=list(run_list.keys()))
if has_baseline:
    baseline_df = pd.read_csv('baseline.csv', index_col=0)

for idx, (name, file) in enumerate(run_list.items()):
    print(f'Running ({idx+1}/{len(run_list)}) {name}...')

    exec_time_list = []
    for n in range(RUN_ITER):
        exec_time = -1
        try:
            stime = time.time()
            subprocess.run(["./"+TARGET_FILE, f"./PowerGrid/{file}", f"./exp/{timestamp}/output/{file}_out.txt"], timeout=MAX_MINUTE*60)
            exec_time = time.time() - stime
            print(f'\t{n+1}. took {exec_time:.4f} seconds.', end='')
            if has_baseline:
                baseline_time = baseline_df.loc[name, 'time(s)']
                if baseline_time == -1:
                    baseline_time = float('inf')
                print(f'({baseline_time/exec_time:.2f}x)')
            else:
                print()
        except subprocess.TimeoutExpired:
            print(f'\t{n+1}. {file} took too long to run.')
        except Exception as e:
            print(f'\t{n+1}. {file} failed to run: {e}')
        exec_time_list.append(exec_time)
    
    avg_exec_time = sorted(exec_time_list)[RUN_ITER//2]
    if has_baseline:
        baseline_time = baseline_df.loc[name, 'time(s)']
        print(f'\toverall speedup: {baseline_time/avg_exec_time:.2f}x')
    df.loc[name] = [file, avg_exec_time]
    print(f'\t{name} done')

if not has_baseline:
    df.to_csv('baseline.csv')
    print('Baseline result saved to baseline.csv')
else:
    df.to_csv(f'exp/{timestamp}/time.csv')
    if is_macos:
        os.system(f'cp {SOURCE_FILE} exp/{timestamp}/{SOURCE_FILE}')
        os.system(f'cp {TARGET_FILE} exp/{timestamp}/{TARGET_FILE}')
    else:
        os.system(f'copy "{SOURCE_FILE}" "exp/{timestamp}/{SOURCE_FILE}"')
        os.system(f'copy "{TARGET_FILE}" "exp/{timestamp}/{TARGET_FILE}"')

    print(f'Experiment result saved to .exp/{timestamp}')

is_end = True