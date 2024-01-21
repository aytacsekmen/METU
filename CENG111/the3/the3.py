def rotate(array):
    length_row=len(array)
    length_column=len(array[0])
    new_array=[[None]*length_row for _ in  range(length_column)]
    for c in range(length_column):
        for r in range(length_row-1,-1,-1):
            new_array[length_column-c-1][r]=array[r][c]
    return new_array

def pattern_search(pattern,image):
    toplam=0
    control=1
    starting_row_index=0
    starting_column_index=0
    length_row=len(pattern)
    length_column=len(pattern[0])
    length_row_image=len(image)
    length_column_image=len(image[0])
    control2=0
    rotated_270=rotate(pattern)
    rotated_180=rotate(rotated_270)
    rotated_90=rotate(rotated_180)
    for i in range (length_row_image-length_row+1):
        for j in range(length_column_image-length_column+1):
            for n in range(length_column):
                for m in range(length_row):
                    if pattern[m][n]==image[i+m][j+n]:
                        if control:
                            starting_row_index=i
                            starting_column_index=j
                            control=0
                        toplam+=1
                    else:
                        toplam=0
                        control=1
                        control2=1
                        break
                if control2:
                    control2=0
                    break
            if toplam==length_row*length_column:
                return (starting_row_index,starting_column_index,0)
            toplam=0
            control=1
    length_row=len(rotated_90)
    length_column=len(rotated_90[0])
    control=1
    toplam=0
    control2=0
    for i in range (length_row_image-length_row+1):
        for j in range(length_column_image-length_column+1):
            for n in range(length_column):
                for m in range(length_row):
                    if rotated_90[m][n]==image[i+m][j+n]:
                        if control:
                            starting_row_index=i
                            starting_column_index=j
                            control=0
                        toplam+=1
                    else:
                        toplam=0
                        control=1
                        control2=1
                        break
                if control2:
                    control2=0
                    break
            if toplam==length_row*length_column:
                return (starting_row_index,starting_column_index,90)
            toplam=0
            control=1
    control=1
    toplam=0
    control2=0
    length_row=len(rotated_180)
    length_column=len(rotated_180[0])
    for i in range (length_row_image-length_row+1):
        for j in range(length_column_image-length_column+1):
            for n in range(length_row):
                for m in range(length_column):
                    if rotated_180[n][m]==image[i+n][j+m]:
                        if control:
                            starting_row_index=i
                            starting_column_index=j
                            control=0
                        toplam+=1
                    else:
                        toplam=0
                        control=1
                        control2=1
                        break
                if control2:
                    control2=0
                    break
            if toplam==length_row*length_column:
                return (starting_row_index,starting_column_index,180)
            toplam=0
            control=1
    length_row=len(rotated_270)
    length_column=len(rotated_270[0])
    control=1
    toplam=0
    control2=0
    for i in range (length_row_image-length_row+1):
        for j in range(length_column_image-length_column+1):
            for n in range(length_column):
                for m in range(length_row):
                    if rotated_270[m][n]==image[i+m][j+n]:
                        if control:
                            starting_row_index=i
                            starting_column_index=j
                            control=0
                        toplam+=1
                    else:
                        toplam=0
                        control=1
                        control2=1
                        break
                if control2:
                    control2=0
                    break
            if toplam==length_row*length_column:
                return (starting_row_index,starting_column_index,270)
            toplam=0
            control=1   
    return False



#P1 = ["AXA", "XAY"]
#P2 = ["AXA", "XAZ"]
#P1=["ayz", "cba"]
#I = ["tuz<abcd", ">#sAY#at", "uzyXAAr.", "r,lAXxio", "z#a!yabc", "yazy?zya"]
#print(pattern_search(P, I))
#print(pattern_search(P2, I))



    
