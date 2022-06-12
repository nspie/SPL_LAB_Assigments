#! /usr/bin/awk -f

BEGIN { FS = ","
        OFS = " - "
        counter = 0
        writing = 0
        reading = 0
        math = 0
        countBech = 0
        countnum = 0
        print "============="
        print "Success Student List"
        print "=============\n"
}

{
    
    if($6 >= 80 and $7 >= 80 and $8 >= 80){
        countnum++;
        print $0
    }
    
    if($4 == "standard"){
        counter++;
        writing += $8
        reading += $7
        math += $6

    }
    
    if($3 == "bachelor's degree")
        countBech++;

}

END{
    printf "The number of students :%d\n", countnum
    
    printf "Avarage fo math is: %d\n", math / counter 
    printf "Avarage fo reading is: %d\n", reading / counter   
    printf "Avarage fo writing is: %d\n", writing / counter 
    print "--------------------"
    
    printf "The number of bachelor's degree :%d\n", countBech
    print "--------------------\n"

}







