def construct_forest(functions):
    return_list=[]
    list1=[]
    
    control=True
    count=0
    number_func=0
    for i in functions:
        functions[count] =i.replace(" ","")
        
        count=count+1
    count=0
    for i in functions:
        functions[count] =i.replace("(x)","")
        
        count=count+1
    for i in functions:
        for b in range(number_func):
            if i.split("=")[0]==list1[b][0]:
                control=False
        if control==True:
            
            list1.append([])
            list1[number_func].append(i.split("=")[0])
            if "*" in i:
                list1[number_func].append("*")
                list1[number_func].append([i.split("*")[0].split("=")[1]])
                list1[number_func].append([i.split("*")[1]])
            elif "^" in i:
                list1[number_func].append("^")
                list1[number_func].append([i.split("^")[0].split("=")[1]])
                list1[number_func].append([i.split("^")[1]])
            elif "-" in i:
                list1[number_func].append("-")
                list1[number_func].append([i.split("-")[0].split("=")[1]])
                list1[number_func].append([i.split("-")[1]])
            elif "+" in i:
                list1[number_func].append("+")
                list1[number_func].append([i.split("+")[0].split("=")[1]])
                list1[number_func].append([i.split("+")[1]])
            number_func=number_func+1
    #buraya kadar olan kısımda her bir elemanı ayırdım sıra kontrol etmede
    copy_list=list(list1)
    #print(copy_list)


    #listem bu şekilde:
    #[['h(x)', '*', ['c(x)'], ['6']],
    #['c(x)', '+', ['f(x)'], ['33']],
    #['e(x)', '+', ['x'], ['45']],
    #['f(x)', '*', ['m(x)'], ['52']],
    #['m(x)', '^', ['e(x)'], ['89']]]

    change_count=10
    control=True
    control2=True
    while change_count!=0:
        change_count=0
        while control:

            for i in copy_list:
                for j in copy_list:
                    if i[2][0]==j[0]:
                        if not i[2]==list(j):
                            i[2]=list(j)
                            change_count+=1
                            control=False
                            control2=False
                    if control2==False:
                        control2=True
                        break
                    
            if not control:
                control=True

            else:
                break

            
        control=True
        control2=True
        while control:

            for i in copy_list:
                for j in copy_list:
                    if i[3][0]==j[0]:
                        if not i[3]==list(j):
                            i[3]=list(j)
                            change_count+=1
                            control=False
                            control2=False
                    if control2==False:
                        control2=True
                        break
            if not control:
                control=True

            else:
                break
    #fonksiyonları ayarladık



#listeye ekleme
    control12=True
    for count1,value1 in enumerate(copy_list):
        for count2,value2 in enumerate(copy_list):
            if value1[0] in str(value2) and count1!=count2:
                control12=False
                break
        if control12==False:
            control12=True
            continue
        else:
            return_list.append(value1)

    return return_list