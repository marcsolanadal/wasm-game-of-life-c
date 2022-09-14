set width 0
set height 0
set verbose off
set pagination off
set logging file output.txt
set logging overwrite on
set logging enabled on

break 26
run

display x
display y
display j
display k
display count

command 1
    info display
    continue
end


