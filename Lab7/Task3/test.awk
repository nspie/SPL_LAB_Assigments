#! /usr/bin/awk -f

BEGIN { FS = ","
        OFS = "---"
        counter = 0

}

{
    
    
    if(/spring/){
        print $2, $3, $4
    }
    
    if($2 ~/happy/)
        print $2, $3, $4
    
    if(/fan | fun/)
        counter++;

}

END{
    printf "\n------------------------------\nThe number of poem that have fun or fan is : %d\n", counter

}







