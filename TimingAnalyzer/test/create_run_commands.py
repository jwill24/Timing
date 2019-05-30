#! make commands for crab input

def split( infilename, outfilename, start, stop ):

        infile = open( infilename, 'r' )
        outfile = open( outfilename, 'w' )

        for line in infile:
                outline = line
                num = line.split(':')
                run = int( num[0] )
                print( run )
                if( ( run >= start ) and ( run <= stop ) ):
                        #print( "writing: " + outline )
                        outfile.write( outline )
                elif run > stop : break

        infile.close()
        outfile.close()

#   Run 315257 : 315322 GranTotal: 2744
#   subcrab( "315257-315322", event_list_path + "sorted_event_list_315257v315322_EG2018A.txt" )
#   split( "sorted_event_list_EG2018A.txt", "sorted_event_list_315257v315322_EG2018A.txt", 315257, 315322 )
#   >>>> START ERA A

def make_commands( inputfilename ):

	infile = open( inputfilename, 'r' )
        splitfile = open( "split_list.txt", 'w' )
        crabfile = open( "crab_input_list.txt", 'w' )

	year = 'EG2018'
	era = '' 
	for line in infile:
		line = line.rstrip()
		#print('------------' + line )
		if "START" in line:
			lsplit = line.split( ' ' )
			#print( lsplit[0] + '-' + lsplit[1] + '-' + lsplit[2] + '-' + lsplit[3] )
			era = lsplit[3]
		sstart = 'split( \"sorted_event_list_' + year + era + '.txt\", \"sorted_event_list_'
		smid = '_' + year + era + '.txt\", '
		cstart = 'subcrab( \"'
		cmid = '\", event_list_path + \"sorted_event_list_'
		cend = '_' + year + era + '.txt\" )\n'
		if "GranTotal" in line :
			getline = line.split(' ')
			#print( sstart + getline[1] + 'v' + getline[3] + smid + getline[1] + ', ' + getline[3] + ' )' )
			splitfile.write( sstart + getline[1] + 'v' + getline[3] + smid + getline[1] + ', ' + getline[3] + ' )\n' )
			#print( cstart + getline[1] + '-' + getline[3] + cmid  + getline[1] + 'v' + getline[3] + cend )
			crabfile.write( cstart + getline[1] + '-' + getline[3] + cmid  + getline[1] + 'v' + getline[3] + cend )






make_commands( 'Run2018_run_lumi.txt' )
