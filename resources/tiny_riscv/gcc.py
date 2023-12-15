#!/usr/bin/env python3

import sys, re, os, mimetypes, argparse, requests, json

parser = argparse.ArgumentParser(description='Compiles a C program into a gcc output x86_64.')

flags = {"march": "-march=rv32im",
         "mabi":  "-mabi=ilp32",
         "tldp": "-fno-tree-loop-distribute-patterns",
         "relax": "-mno-relax",
         "static": "-static",
         "nsf": "-nostartfiles",
         "nstdlib": "-nostdlib",
         "opt0": "-O0",
         "opt1": "-O1",
         "opt2": "-O2"
        }

for key, value in flags.items():
  parser.add_argument(value, dest=key, action='store_const',
                      const=True, default=False,
                      help='')

parser.add_argument('-o', dest='output',
                    help='Write output to this file')
parser.add_argument('files', metavar='C-files', nargs="+",
                    help='translates and assembles file')


# %.riscv: %.c lib.c Makefile
# ./gcc -march=rv32im -mabi=ilp32 -fno-tree-loop-distribute-patterns -mno-relax
# -O1 $< lib.c -static -nostartfiles -nostdlib -o $@


args = parser.parse_args()


parsedflags = ""
for key, value in flags.items():
  if vars(args)[key]:
    parsedflags += value
    parsedflags += " "

DATA = {}
DATA["flags"] = parsedflags

num = 1
use_assembler = False

for f in args.files:
  extensions = f.split(".")
  fileextension = extensions[-1]

  if fileextension == 's':
    use_assembler  = True


for f in args.files:
  extensions = f.split(".")
  fileextension = extensions[-1]

  if fileextension != "c" and fileextension != 's':
    print("The input is expected to be a C or Assembly program; fileextension 'c' or 's'.\n")
    exit()

  if not os.path.isfile(f):
    print("Input file does not exist: "+f+"\n")
    exit()

  os.system("cat "+f+" | cpp > "+f+"_cpp")

  file = open(f+"_cpp", 'r')
  DATA["filename"+str(num)] = f
  DATA["filecont"+str(num)] = file.read()
  file.close()

  os.system("rm "+f+"_cpp")
  num = num + 1

# print(args)

# print(DATA)

# x86prime Online location
URL = "http://topps.diku.dk/compsys/gcc-cross.php"
if use_assembler:
  URL = "http://topps.diku.dk/compsys/asm-cross.php"

# defining a params dict for the parameters to be sent to the API
# DATA = {"filename":args.file, "file":args.fileCont, "march":args.march, "mabi":args.Wextra, "Winline":args.Winline, "pedantic":args.pedantic, "osc":args.osc, "protect":args.protect}
# sending get request and saving the response as response object
r = requests.post(url = URL, data = DATA)

URLDIR = "http://topps.diku.dk/compsys/gcc_runs/"
# extracting data in json format
runid = r.text

# print(runid)

error = requests.get(url = URLDIR+runid+".error")

if args.output == None:
  outname = args.files[0][:-2] + ".elf"
else:
  outname = args.output

if error.text != "":
  print(error.text)
  exit()
else:
  assembler = requests.get(url = URLDIR+runid+".elf")

  # if args.output != None:
  file = open(outname, 'wb')
  args.fileCont = file.write(assembler.content)
  file.close()
  # else:
  #   print(assembler.text)

