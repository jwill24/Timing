
#324420
#()
#: [[1, 625]],


def main():

	fi = open( "Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON.txt", "r" )
	line = fi.read()

	line = line.replace( '\"','' )
        line = line.replace( ':','' )
        line = line.replace( ']','' )
        line = line.replace( '[','' )
        line = line.replace( ',','' )
        line = line.replace( '{','' )
        line = line.replace( '}','' )


#	print( line )	

	ent = line.split(" ")
	first = False
	pair = False
	total = 0
	run = 0
	grandtotal = 0
	startrun = 0

	for num in ent :
		if( int(num) > 10000 ) :
			print( "Run: "+str(run)+" Lumi: "+ str(total) )
			if( grandtotal > 2500 ) :
				print( "Run " + str(startrun) + " : " + str(run) + " GranTotal: " + str(grandtotal) )
				grandtotal = 0
				startrun = int(num)  
			run =  int(num)
			total = 0
			first = True
		elif( first ):
			start = int( num )
			first = False
		else :
			total = total + int( num ) - start
			grandtotal = grandtotal + int( num ) - start
			first = True


main()
