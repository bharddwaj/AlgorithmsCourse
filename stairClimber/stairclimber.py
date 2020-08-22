"""
Basic (not most efficient) algorithm for generating all ways to
climb n stairs, going up 1, 2, or 3 stairs at a time.

Last modified: February 19, 2019
"""
def get_ways(num_stairs):
    ways = []
    if num_stairs <= 0:
        ways.append([])
    else:
        for i in range(1, 4):
            if num_stairs >= i:
                result = get_ways(num_stairs - i)
                #print(result)
                for j in range(len(result)):
                    # print(f"jth element of results: {result}")
                    result[j].insert(0, i)
                # print(f"Before: {ways}")
                ways += result
                # print(f"After: {ways}")
    return ways

for way in get_ways(4):
    print(way)
    break
