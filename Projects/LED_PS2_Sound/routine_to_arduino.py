#! /usr/bin/env python
"""
protocol.h parser

Written by Carlos Chinchilla
All rights reserved
"""

import sys
import argparse

MAX_CASES = 255

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-r", "--routine-file", help="input file with routines")
    parser.add_argument("-s", "--template-file", help="input template and output file")
    parser.add_argument("-c", "--start-case", type=int, required=True)
    args = parser.parse_args()
    
    fh = open(args.routine_file,'r')
    routines = fh.readlines()
    fh.close()
    
    # Parse routines
    parsed_routines = []
    r_found = False
    r_temp = ''
    for r in routines:
        if not r_found and "//START:" in r.strip().replace(' ',''):
            r_temp = r
            r_found = True
        elif r_found:
            r_temp += r
            if "//END" in r.strip().replace(' ',''):
                r_found = False
                parsed_routines.append(r_temp)
                #print(r_temp)
    
    print("found %d different routines" % len(parsed_routines))
    if len(parsed_routines) - args.start_case > MAX_CASES:
        print("too many routines, choosing the first %d" (MAX_CASES - args.start_case))
        parsed_routines = parsed_routines[0:MAX_CASES-args.start_case]

    fh = open(args.template_file,'r')
    template = fh.readlines()
    fh.close()
    #Create backup
    with open(args.template_file + '.BACKUP','w') as fh_b:
        for l in template:
            fh_b.write(l)

    # Make template output file
    with open(args.template_file,'w') as fh_o:
        start_found = end_found = False
        for line in template:
            if not start_found:
                fh_o.write(line)
                if'/* ROUTINES START */' in line:
                    start_found = True
                    print("writing routines with cases")
                    case = args.start_case
                    for r in parsed_routines:
                        fh_o.write("  case %d:\n" % case)
                        case += 1
                        fh_o.write(r)
                        fh_o.write('      if(continuous_flow) effect++; break;\n')
            else:
                if '/* ROUTINES END */' in line:
                    end_found = True
            if end_found:
                fh_o.write(line)

