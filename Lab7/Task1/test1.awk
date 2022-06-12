#! /usr/bin/awk -f

BEGIN { FS = ","
        OFS = " - "
}

{
    if($2 >= 1970){
        printf "Actor Name: %s\n",$4
        printf "Movie Name: %s\n", $4
        print "---------------------"
    }

}



