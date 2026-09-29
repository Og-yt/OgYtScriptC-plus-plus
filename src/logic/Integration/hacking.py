import sys
import json

for line in sys.stdin:
    data = json.loads(line)
    
    print(
        f'{data['function']} '
        f'line={data['line']}: {data['message']}',
        flush=True
    )
    
