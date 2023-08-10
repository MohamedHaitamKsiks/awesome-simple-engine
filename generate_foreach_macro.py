import sys

#file path
file_path = "asengine/engine/Macros/Foreach.h"

# include guards
file_head = '''
    #ifndef ASENGINE_MACRO_FOREACH_H
    #define ASENGINE_MACRO_FOREACH_H
'''
file_end = "#endif // ASENGINE_MACRO_FOREACH_H"

#get max agrugment 
assert (len(sys.argv) == 2)
max_aguments = int(sys.argv[1])

#generate code
code = [file_head]

# add first line 
code.append(f'''
    #define FOREACH(macro, arg, ...) \\
    macro(arg)                  \\
     __VA_OPT__(FOREACH_{max_aguments}(macro, __VA_ARGS__))
''')

#generate middle steps
for i in range(1, max_aguments):
    code.append(f'''
    #define FOREACH_{i+1}(macro, arg, ...) \\
    macro(arg)                  \\
     __VA_OPT__(FOREACH_{i}(macro, __VA_ARGS__))
''')

#generate final step
code.append("\n#define FOREACH_1(macro, arg) (macro(arg))\n\n")
code.append(file_end)

#save to file
file = open(file_path, "w")

file.write(''.join(code))
file.close()