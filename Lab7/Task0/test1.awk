#! /usr/bin/awk -f

BRGIN{FS = ""}
{
    
A[$3]++;

}

END {
        printf "count: " A["English"]
        printf "\n"

}


