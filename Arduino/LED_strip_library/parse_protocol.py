#! /usr/bin/env python
"""
protocol.h parser

Written by Carlos Chinchilla
All rights reserved
"""

if __name__ == "__main__":
    fh = open("protocol.h",'r')
    lines = fh.readlines()
    fh.close()
    with open("protocol.py",'w') as fh:
        fh.write("passed = False\n")
        themes_list = []
        effects_list = []
        for line in lines:
            if line.strip().replace(' ','').startswith("#define"):
                l = line.replace('\n','').split(' ')
                variable = l[1]
                value = l[2]
                msg = "%s = %s" % (variable, value)
                fh.write(msg+'\n')
                print(msg)
                
                if "_THEME" in variable:
                    themes_list.append((variable.replace('_THEME',''),variable))
                elif "_EFFECT" in variable:
                    effects_list.append((variable.replace('_EFFECT',''),variable))

        # Parse theme constants
        fh.write('themes_list = {\n')
        for t_name,t_variable in themes_list:
            fh.write("'%s':%s,\n" % (t_name,t_variable))
        fh.write('}\n')

        # Parse effect constants
        fh.write('effects_list = {\n')
        for t_name,t_variable in effects_list:
            fh.write("'%s':%s,\n" % (t_name,t_variable))
        fh.write('}\n')
        
        # add passed flag
        msg = "passed = True"
        fh.write(msg+'\n')
        print(msg)
    
    import protocol
    if protocol.passed:
        print("parsing done successfully")
    else:
        print("unsuccessful parsing")
