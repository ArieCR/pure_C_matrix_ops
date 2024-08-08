import numpy as np
import os.path

def to_list(mat):
	return list(mat.flat)
def create_matrix_and_inverse(n):
	while True :
		mat = np.random.randint(0,10, size = (n,n))
		if(abs(np.linalg.det(mat)) > 0.0000001):
			break 
	inv_mat = np.linalg.inv(mat)
	return to_list(np.float64(mat)), to_list(np.float64(inv_mat))

def create_2_matrices_and_mult(a,b,c):
	mat1 = np.random.randint(0,10, size = (a,b))
	mat2 = np.random.randint(2,44, size = (b,c))
	mat3 = mat1@mat2
	return to_list(np.float64(mat1)),to_list(np.float64(mat2)),to_list(np.float64(mat3))
def mult(a,b,c):
	x,y,z = create_2_matrices_and_mult(a,b,c)
	my_list = x,y,z
	my_list = [nparray_2_C_string(x,"arr"+"1") for x in my_list]
	for j in my_list:
		continue#print(j+"\n") 
	return my_list
def inverse(n):
	x,y = create_matrix_and_inverse(n)
	name = "arr" +str(1)
	x1 = nparray_2_C_string(x,name)
	x2 = nparray_2_C_string(y,name+"inv")
	my_list = x1,x2
	#print(x1+"\n")
	#print(x2)
	return my_list
def nparray_2_C_string(arr,name):
	str1 = "double " + name +"["+str(len(arr))+"]" "=" + "{"
	for i in arr: 
		str1 = str1 +str(i)+ ","
	str1 = str1[:-1] + "}"
	str1 = str1 + ";"
	return str1 
def create_inverse_file(n):
	i = 1
	mat_and_inverse = inverse(n)
	str1 = "inverse_"+str(n)+"_"
	while True:
		if True == os.path.isfile(str1+str(i)):
			i+=1
		else: 
			break
	with open (str1+str(i),'w') as file:
		
		file.write(mat_and_inverse[0])
		file.write("\n")
		file.write(mat_and_inverse[1])
		
def create_mult_file(a,b,c):
	i = 1
	mats_and_res = mult(a,b,c)
	name = "mult"+"_"+str(a)+"_"+str(b)+"_"+str(c)+"_"
	while True:
		if True == os.path.isfile(name+str(i)):
			i+=1
		else: 
			break
	with open (name+str(i),'w') as file:
		file.write(mats_and_res[0])
		file.write("\n")
		file.write(mats_and_res[1])
		file.write("\n")
		file.write(mats_and_res[2])

def main():
	while True:
		x = input("Enter your choice, q for quit, I for inverse, M for mult,G for generate\n")
		if x == "q":
			return
		if x == "I":
			inverse(5)
			break
		if x == "M":
			mult(5)
			break
		if x == "G":
			rand = np.random.randint(2,22,size = (1,3))
			create_mult_file(rand[0][0],rand[0][1],rand[0][2])
			create_inverse_file(5)
				
			
			
if __name__ == "__main__":
	main()
