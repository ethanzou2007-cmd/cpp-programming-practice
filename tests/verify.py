from pathlib import Path
import subprocess
import itertools
import math
import re
import sys

BUILD = Path(sys.argv[1]) if len(sys.argv) > 1 else Path("build")

count = 0
def check(name, data, expected, status=0):
    global count
    r = subprocess.run([str(BUILD / (name + '.exe'))], input=data,
                       text=True, capture_output=True, timeout=3)
    assert r.returncode == status and expected in r.stdout, (name, data, r.returncode, r.stdout)
    count += 1

for mood, time, weather in itertools.product(range(1, 6), 'MAE', 'SR'):
    expected = ('Relaxing piano music' if weather == 'R' else
                ('Upbeat pop music' if time in 'MA' else 'Smooth jazz') if mood >= 4 else
                ('Acoustic guitar ballads' if time in 'MA' else 'Ambient electronic music'))
    check('music_selector', f'{mood} {time} {weather}', expected)
for data in ['0 M S', '6 M S', '4 X S', '4 M X', 'x M S', '', '4', '4 M', '4 m S']:
    check('music_selector', data, 'Invalid input.', 1)
for status in range(16):
    expected = ('kitchen fan' if status & 4 else 'bathroom heater' if status & 8 else
                'living room air conditioner' if status & 1 else 'bedroom air conditioner' if status & 2 else 'standby mode')
    check('energy_saver', str(status), expected)
for data in ['-1', '16', 'x', '']:
    check('energy_saver', data, 'Invalid status value.', 1)
for moisture in [0, 19, 20, 79, 80, 100]:
    for days in [0, 5, 6]:
        expected = ('Water immediately!' if moisture < 20 else 'Time to water your plant.' if days > 5 else
                    'Check drainage.' if moisture >= 80 else 'Your plant is happy!')
        check('plant_water', f'{moisture} {days}', expected)
for data in ['-1 0', '101 0', '50 -1', 'x', '']:
    check('plant_water', data, 'Invalid input.', 1)
for code, price, item in [('A',150,'Water'), ('B',200,'Juice'), ('C',250,'Cola')]:
    check('vending', f'{price-1} {code}', 'Insufficient money.')
    check('vending', f'{price} {code}', f'Purchased {item}. No change.')
    check('vending', f'{price+10} {code}', 'Your change is 10 cents.')
check('vending', '-1 A', 'Invalid money amount.', 1)
check('vending', '150 X', 'Invalid item code.', 1)
check('vending', 'x A', 'Invalid money amount.', 1)
check('bmi_calculator', '70 1.75', '22.86')
for data in ['70 0', '-1 1.75', '70 -1', 'x', '', '1e308 1e-308']:
    check('bmi_calculator', data, 'Invalid input.', 1)
check('street_light_controller', '1 7 1 0 3 7 2 0 4 170 5 10 6', 'Final state: 10100000')
check('street_light_controller', '4 255 6', 'Final state: 11111111')
check('street_light_controller', '4 128 6', 'Final state: 10000000')
check('street_light_controller', '4 0 6', 'Final state: 00000000')
check('street_light_controller', '9 6', 'Invalid option, please try again.')
for data, message in [('1 -1','Invalid lamp number.'), ('2 8','Invalid lamp number.'),
                      ('3 x','Invalid lamp number.'), ('4 -1','Invalid mask.'), ('5 256','Invalid mask.'),
                      ('4 x','Invalid mask.'), ('','Invalid input.')]:
    check('street_light_controller', data, message, 1)


def run(name, data='', status=0):
    global count
    result = subprocess.run([str((BUILD / (name + '.exe')).resolve())], input=data,
                            text=True, capture_output=True, timeout=5)
    assert result.returncode == status, (name, data, result.returncode, result.stdout, result.stderr)
    count += 1
    return result.stdout + result.stderr

def near(actual, expected, tolerance=0.051):
    assert abs(float(actual) - expected) <= tolerance, (actual, expected)

# Compare population count with Python's independent integer representation.
values = list(range(1, 65)) + [127, 128, 255, 256, 1023, 1024, 1073741824, 2147483647]
out = run('bit_detective', '\n'.join(map(str, values)) + '\n0\n')
rows = re.findall(r'Decimal (\d+) has (\d+) 1-bits', out)
assert [(int(a), int(b)) for a, b in rows] == [(v, v.bit_count()) for v in values]
for v in values:
    assert f'{v} is {"" if v & (v - 1) == 0 else "not "}a power of two.' in out
assert 'Negative invalid' in run('bit_detective', '-2\n7\n0\n')
assert 'Program ended.' in run('bit_detective', '0\n')
for data in ['', '  ', '12\n', '-1\n']:
    run('bit_detective', data)
for data in ['x\n', '1.5\n', '2147483648', '999999999999999999999\n', '12x\n', '8\nx\n']:
    assert 'Invalid integer' in run('bit_detective', data, 1)

# Generate primes independently using a sieve and check every representation.
primes = [True] * 1001
primes[0] = primes[1] = False
for p in range(2, 32):
    if primes[p]:
        for multiple in range(p * p, len(primes), p):
            primes[multiple] = False
for n in list(range(4, 202, 2)) + [1000]:
    out = run('goldbach_conjecture_verification', str(n) + '\n')
    actual = [(int(a), int(b)) for a, b in re.findall(r' = (\d+) \+ (\d+)', out)]
    expected = [(p, n-p) for p in range(2, n//2 + 1) if primes[p] and primes[n-p]]
    assert actual == expected, (n, actual, expected)
    assert f'Total {len(expected)} representations found.' in out
assert '10 = 3 + 7' in run('goldbach_conjecture_verification', '-2\n0\n2\n3\n10\n')
for data in ['', '  ', '3\n']:
    run('goldbach_conjecture_verification', data)
for data in ['x', '4.5', '4x', '2147483648', '999999999999999999999\n']:
    assert 'Invalid integer' in run('goldbach_conjecture_verification', data, 1)

# Thresholds refer to total > 200, including totals split across items.
for items in [[1], [199.99], [200], [200.01], [100, 100], [100, 100.01], [150, 60], [0.1, 0.2]]:
    out = run('supermarket_checkout_system', '\n'.join(map(str, items + [0])) + '\n')
    assert f'Number of items: {len(items)}' in out
    assert f'Total: {sum(items):.2f} yuan' in out
    assert f'Average price: {sum(items)/len(items):.2f} yuan' in out
    assert ('get a coupon' in out) == (sum(items) > 200)
out = run('supermarket_checkout_system', '0\n-1\n50\n-5\n0\n')
assert 'Must enter at least one' in out and 'Number of items: 1' in out and 'Total: 50.00' in out
for data in ['', '0\n', '10\n', 'x\n', '10\nx\n', '2x\n0\n', 'nan\n', 'inf\n', '1e309\n', '1e308\n1e308\n0\n']:
    run('supermarket_checkout_system', data, 1)

out = run('hundred_monks_and_hundred_buns')
actual = [tuple(map(int, row.split())) for row in out.splitlines() if re.fullmatch(r'\d+\t\d+\t\d+', row)]
expected = [(a, b, c) for a in range(101) for b in range(101) for c in [100-a-b]
            if c >= 0 and 3*a + 2*b + c/3 == 100]
assert actual == expected and f'Total {len(expected)} solutions found.' in out

out = run('one_hot_encoding_generator')
labels = [2, 0, 4, 1, 3, 2, 0, 4, 3, 1, 0, 2]
rows = re.findall(r'Label (\d+) -> \[([01, ]+)\]', out)
assert len(rows) == len(labels)
for label, (printed, vector) in zip(labels, rows):
    assert int(printed) == label
    assert list(map(int, vector.split(', '))) == [int(i == label) for i in range(5)]
for i in range(5):
    assert f'{i}:{labels.count(i)}times' in out

out = run('signal_smoother')
raw = [35.2,36.1,34.8,89.3,35.5,36.0,34.9,35.8,36.3,35.0]
rows = [r.split() for r in out.splitlines() if re.fullmatch(r'\s*\d+\s+[+-]?[\d.]+\s+[+-]?[\d.]+', r)]
assert len(rows) == len(raw)
for i, row in enumerate(rows):
    assert int(row[0]) == i
    near(row[1], raw[i])
    near(row[2], raw[i] if i in (0, len(raw)-1) else sum(raw[i-1:i+2])/3)

out = run('temperature_statistics_tool')
temps = [-2,-2.5,-3,-3.2,-3.5,-4,-3.8,-2,1,4.5,7,9.5,11,12.5,13,12.8,10,7.2,5,2.5,1,0,-1.2,-1.8]
mean = sum(temps)/len(temps)
near(re.search(r'total temperature: ([\d.-]+)', out)[1], sum(temps))
near(re.search(r'mean temperature:\s+([\d.-]+)', out)[1], mean)
assert 'Maximum temperature: 13.0 degrees, occurred at 14:00' in out
assert 'Minimum temperature: -4.0 degrees, occurred at 5:00' in out
assert f'Hours below freezing: {sum(t < 0 for t in temps)} hours' in out
rows = [r.split() for r in out.splitlines() if re.fullmatch(r'\s*\d+\s+[+-]?[\d.]+\s+[+-]?[\d.]+', r)]
assert len(rows) == 24
for i, row in enumerate(rows):
    assert int(row[0]) == i
    near(row[1], temps[i])
    near(row[2], temps[i]-mean)

# This exercise generates crossover signals; it does not simulate portfolio returns.
out = run('quantitative_trading_backtest_engine')
prices = [100,102.5,101.8,103.2,104,105.5,107,106.3,108.1,109.5,110.2,111,109.8,108.4,107,106.5,107.8,109.2,110.5,112,113.5,114.8,113,111.2,110,108.5,109.8,111.5,113.2,115]
rows = [r.split() for r in out.splitlines() if re.match(r'^\d+\t', r)]
assert len(rows) == 30
signals = []
ma5 = [None if i < 4 else sum(prices[i-4:i+1])/5 for i in range(30)]
ma10 = [None if i < 9 else sum(prices[i-9:i+1])/10 for i in range(30)]
for i, row in enumerate(rows):
    assert int(row[0]) == i+1
    near(row[1], prices[i], 0.0051)
    for actual, expected in [(row[2],ma5[i]), (row[3],ma10[i])]:
        if expected is None:
            assert actual == '---'
        else:
            near(actual, expected, 0.0051)
    signal = 'HOLD'
    if i >= 10:
        if ma5[i-1] <= ma10[i-1] and ma5[i] > ma10[i]:
            signal = 'BUY'
        elif ma5[i-1] >= ma10[i-1] and ma5[i] < ma10[i]:
            signal = 'SELL'
    assert row[4] == signal
    signals.append(signal)
for signal in ['BUY', 'SELL']:
    assert f'{signal} signals: {signals.count(signal)}' in out

print(f'PASS: {count} program executions, all assertions passed; all 14 programs covered.')
