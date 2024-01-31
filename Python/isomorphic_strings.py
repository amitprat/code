def are_isomorphs(s1, s2):
    if len(s1) != len(s2) or len(set(a)) != len(set(b)):
        return False
    s1_cd = string_color_distribution(s1)
    s2_cd = string_color_distribution(s2)

    for i, color in enumerate(s1_cd):
        if color != s2_cd[i]:
            return False
    return True

def string_color_distribution(s):
    max_color_so_far = -1
    color_mapping = {}
    color_distribution = []

    for c in s:
        if c in color_mapping:
            curr_color = color_mapping[c]
        else:
            curr_color = max_color_so_far + 1
            max_color_so_far += 1
            color_mapping[c] = curr_color

        color_distribution.append(curr_color)
    
    return color_distribution

a = input()
b = input()
print(are_isomorphs(a,b))