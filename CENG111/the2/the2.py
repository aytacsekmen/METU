coordinates=eval(input())
vertex0=coordinates[0]
vertex0_x=vertex0[0]
vertex0_y=abs(vertex0[1])
vertex1=coordinates[1]
vertex1_x=vertex1[0]
vertex1_y=abs(vertex1[1])
vertex2=coordinates[2]
vertex2_x=vertex2[0]
vertex2_y=abs(vertex2[1])
vertex3=coordinates[3]
vertex3_x=vertex3[0]
vertex3_y=abs(vertex3[1])
max_x_value=0
max_x_y_value=0
min_x_value=0
min_x_y_value=0
min_x_value=vertex0_x
min_x_y_value=vertex0_y
min_x="0"
if vertex1_x<min_x_value:
    min_x_value=vertex1_x
    min_x_y_value=vertex1_y
    min_x="1"
elif vertex1_x==min_x_value and vertex1_y<min_x_y_value:
    min_x_y_value=vertex1_y
    min_x="1"
if vertex2_x<min_x_value:
    min_x_value=vertex2_x
    min_x_y_value=vertex2_y
    min_x="2"
elif vertex2_x==min_x_value and vertex2_y<min_x_y_value:
    min_x_y_value=vertex2_y
    min_x="2"
if vertex3_x<min_x_value:
    min_x_value=vertex3_x
    min_x_y_value=vertex3_y
    min_x="3"
elif vertex3_x==min_x_value and vertex3_y<min_x_y_value:
    min_x_y_value=vertex3_y
    min_x="3"
max_x_value=vertex0_x
max_x_y_value=vertex0_y
max_x="0"
if vertex1_x>max_x_value:
    max_x_value=vertex1_x
    max_x_y_value=vertex1_y
    max_x="1"
elif vertex1_x==max_x_value and vertex1_y<max_x_y_value:
    max_x_y_value=vertex1_y
    max_x="1"
if vertex2_x>max_x_value:
    max_x_value=vertex2_x
    max_x_y_value=vertex2_y
    max_x="2"
elif vertex2_x==max_x_value and vertex2_y<max_x_y_value:
    max_x_y_value=vertex2_y
    max_x="2"
if vertex3_x>max_x_value:
    max_x_value=vertex3_x
    max_x_y_value=vertex3_y
    max_x="3"
elif vertex3_x==max_x_value and vertex3_y<max_x_y_value:
    max_x_y_value=vertex3_y
    max_x="3"
trapezoid_hight=max_x_value-min_x_value
trapezoid_surface=(max_x_y_value+min_x_y_value)/2
trapezoid_area=trapezoid_surface*trapezoid_hight
trapezoid_slope=(max_x_y_value-min_x_y_value)/(max_x_value-min_x_value)
points_under_curve=0    
final_area=0
triangle_area=0
area_of_quadrilateral=0
if not (int(max_x)+int(min_x))%2:
    check_list=[]
    check1=(int(max_x)+1)%4
    check2=(int(min_x)+1)%4
    point1=coordinates[check1]
    point2=coordinates[check2]
    control1=True
    point1_x=point1[0]
    point1_y=abs(point1[1])
    point1_check_slope=False
    point2_check_slope=False
    if not point1_x==min_x_value:
        point1_slope=(point1_y-min_x_y_value)/(point1_x-min_x_value)
    else:
        point1_check_slope=True
    point2_x=point2[0]
    point2_y=abs(point2[1])
    if not point2_x==min_x_value:
        point2_slope=(point2_y-min_x_y_value)/(point2_x-min_x_value)
    else :
        point2_check_slope=True    
    if  not point1_check_slope:
        if point1_slope<trapezoid_slope:
            points_under_curve+=1
    if  not point2_check_slope:
        if point2_slope<trapezoid_slope:
            points_under_curve+=1
    if points_under_curve==0:
        if not point1_check_slope and not point2_check_slope and  point2_slope<point1_slope:
            triangle_area=abs(0.5*(point2_x*(max_x_y_value-min_x_y_value)+max_x_value*(min_x_y_value-point2_y)+min_x_value*(point2_y-max_x_y_value)))
            final_area=trapezoid_area+triangle_area
        elif not point1_check_slope and not point2_check_slope and point2_slope>point1_slope:
            triangle_area=abs(0.5*(point1_x*(max_x_y_value-min_x_y_value)+max_x_value*(min_x_y_value-point1_y)+min_x_value*(point1_y-max_x_y_value)))
            final_area=trapezoid_area+triangle_area
        elif point1_check_slope:
            triangle_area=abs(0.5*(point2_x*(max_x_y_value-min_x_y_value)+max_x_value*(min_x_y_value-point2_y)+min_x_value*(point2_y-max_x_y_value)))
            final_area=trapezoid_area+triangle_area
        elif point2_check_slope:
            triangle_area=abs(0.5*(point1_x*(max_x_y_value-min_x_y_value)+max_x_value*(min_x_y_value-point1_y)+min_x_value*(point1_y-max_x_y_value)))
            final_area=trapezoid_area+triangle_area
    if points_under_curve==1:
        if point1_check_slope==False and trapezoid_slope>point1_slope:
            triangle_area=abs(0.5*(point1_x*(max_x_y_value-min_x_y_value)+max_x_value*(min_x_y_value-point1_y)+min_x_value*(point1_y-max_x_y_value)))
            final_area=trapezoid_area-triangle_area
        elif point2_check_slope==False and point2_slope<trapezoid_slope:
            triangle_area=abs(0.5*(point2_x*(max_x_y_value-min_x_y_value)+max_x_value*(min_x_y_value-point2_y)+min_x_value*(point2_y-max_x_y_value)))
            final_area=trapezoid_area-triangle_area
        #Area =1/2[x1(y2 - y3) + x2(y3 - y1) + x3(y1 - y2)]
    if points_under_curve==2:
        if point2_slope<point1_slope:
            triangle_area=abs(0.5*(point2_x*(max_x_y_value-min_x_y_value)+max_x_value*(min_x_y_value-point2_y)+min_x_value*(point2_y-max_x_y_value)))
            final_area=trapezoid_area-triangle_area
        elif point2_slope>point1_slope:
            triangle_area=abs(0.5*(point1_x*(max_x_y_value-min_x_y_value)+max_x_value*(min_x_y_value-point1_y)+min_x_value*(point1_y-max_x_y_value)))
            final_area=trapezoid_area-triangle_area
        #if point2_y>point1_y:
        #    triangle_area=0.5*(point1_x*(max_x_y_value-min_x_y_value)+max_x_value*(min_x_y_value-point1_y)+min_x_value*(point1_y-max_x_y_value))
        #    final_area=trapezoid_area-triangle_area
        #elif point2_y<point1_y:
        #    triangle_area=0.5*(point2_x*(max_x_y_value-min_x_y_value)+max_x_value*(min_x_y_value-point2_y)+min_x_value*(point2_y-max_x_y_value))
        #    final_area=trapezoid_area-triangle_area
if (int(max_x)+int(min_x))%2:
    check_list=["0","1","2","3"]
    check1=int(max_x)
    check2=int(min_x)
    new_check_list=[str(check1),str(check2)]
    check_list.remove(new_check_list[0])
    check_list.remove(new_check_list[1])
    point1=coordinates[int(check_list[0])]
    point2=coordinates[int(check_list[1])]
    point1_x=point1[0]
    point1_y=abs(point1[1])
    point1_check_slope=False
    point2_check_slope=False
    if not point1_x==min_x_value:
        point1_slope=(point1_y-min_x_y_value)/(point1_x-min_x_value)
    else:
        point1_check_slope=True
    point2_x=point2[0]
    point2_y=abs(point2[1])
    if not point2_x==min_x_value:
        point2_slope=(point2_y-min_x_y_value)/(point2_x-min_x_value)
    else:
        point2_check_slope=True
    #point2_slope_rounded=round(point2_slope,7)
    #point1_slope_rounded=round(point1_slope,7)
    if  not point1_check_slope:
        if point1_slope<trapezoid_slope:
            points_under_curve+=1
    if  not point2_check_slope:
        if point2_slope<trapezoid_slope:
            points_under_curve+=1
    area_of_quadrilateral=abs(vertex0_x*vertex1_y-vertex1_x*vertex0_y+vertex1_x*vertex2_y-vertex2_x*vertex1_y+vertex2_x*vertex3_y-vertex3_x*vertex2_y+vertex3_x*vertex0_y-vertex0_x*vertex3_y)*0.5
    if points_under_curve>0:
        final_area=trapezoid_area-area_of_quadrilateral
    #Area of any kind of Quadrilateral except self intersecting: A+B=(x0y1−x1y0)+(x1y2−x2y1)+(x2y3−x3y2)+(x3y0−x0y3)
    if points_under_curve==0:
        final_area=trapezoid_area
print("{:.2f}".format(final_area))