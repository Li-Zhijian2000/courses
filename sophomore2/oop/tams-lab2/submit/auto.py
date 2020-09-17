# coding = utf-8

import os
import re

output_location = "./submit/src/"
name_patten = "[a-zA-Z]+.java"
for root, dirs, files in os.walk("./src/main/"):
    for file in files:
        # print(file)
        if re.match(name_patten, file) is not None:
            print(os.path.join(root, file))
            in_file = open(os.path.join(root, file), "r")
            out_file = open(os.path.join(output_location, file), "w")
            for code in in_file:
                if re.match("^package[.\n]*", code):
                    continue
                if re.match("^import[.\n]*", code) and not re.match("^import java[.\n]*", code):
                    continue
                # print(code)
                out_file.write(code)
            out_file.close()
