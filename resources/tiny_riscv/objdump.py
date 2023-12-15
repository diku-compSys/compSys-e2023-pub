#!/usr/bin/env python3

import sys, re, os, mimetypes, argparse, requests, json

parser = argparse.ArgumentParser(description='Dumps a riscv elf file to stdout.')

flags = {"optS": "-S",
         "opts": "-s",
         "optw": "-w",
        }

for key, value in flags.items():
  parser.add_argument(value, dest=key, action='store_const',
                      const=True, default=False,
                      help='')

# parser.add_argument('-o', dest='output',
#                    help='Write output to this file')
parser.add_argument('files', metavar='C-files', nargs="+",
                    help='translates and assembles file')



args = parser.parse_args()


parsedflags = ""
for key, value in flags.items():
  if vars(args)[key]:
    parsedflags += value
    parsedflags += " "

DATA = {}
DATA["flags"] = parsedflags

num = 1
for f in args.files:
  extensions = f.split(".")
  fileextension = extensions[-1]

  if fileextension != 'riscv':
    print("The input is expected to be a RISCV Assembly program; fileextension '.riscv'.\n")
    exit()

  if not os.path.isfile(f):
    print("Input file does not exist: "+f+"\n")
    exit()

  # os.system("cat "+f+" | cpp > "+f+"_cpp")

  file = open(f, 'rb')
  DATA["filename"+str(num)] = f
  DATA["filecont"+str(num)] = file.read()
  file.close()

  # os.system("rm "+f+"_cpp")
  num = num + 1

# print(args)

# print(DATA)

# x86prime Online location
URL = "http://topps.diku.dk/compsys/objdump-cross.php"
# defining a params dict for the parameters to be sent to the API
# DATA = {"filename":args.file, "file":args.fileCont, "march":args.march, "mabi":args.Wextra, "Winline":args.Winline, "pedantic":args.pedantic, "osc":args.osc, "protect":args.protect}
# sending get request and saving the response as response object
r = requests.post(url = URL, data = DATA)

URLDIR = "http://topps.diku.dk/compsys/gcc_runs/"
# extracting data in json format
runid = r.text

# print(runid)

error = requests.get(url = URLDIR+runid+".error")

if error.text != "":
  print(error.text)
  exit()
else:
  assembler = requests.get(url = URLDIR+runid+".dis")
  print(assembler.text)

