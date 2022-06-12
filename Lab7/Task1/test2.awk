#! /usr/bin/awk -f

BEGIN { FS = ","
        OFS = " - "
        counter = 0
}

{
    counter++;
    if(counter > 50){
        printf "Movie Name: %s\n", $5
        print "--------------------"
    }

}
