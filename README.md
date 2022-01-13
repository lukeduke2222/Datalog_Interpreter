# Datalog_Interpreter
cs236 Datalog Interpreter

This Project is a Datalog Interpreter written in pure c++

It takes an input file and verifies that it follows a specific grammar.
It then turns the file into useful tables of inputed information that can then be queried.

Example Input:

-----------------------------------------------------

Schemes:
  snap(S,N,A,P)
  csg(C,S,G)
  cn(C,N)
  ncg(N,C,G)

Facts:
  snap('12345','C. Brown','12 Apple St.','555-1234').
  snap('22222','P. Patty','56 Grape Blvd','555-9999').
  snap('33333','Snoopy','12 Apple St.','555-1234').
  csg('CS101','12345','A').
  csg('CS101','22222','B').
  csg('CS101','33333','C').
  csg('EE200','12345','B+').
  csg('EE200','22222','B').

Rules:
  cn(c,n) :- snap(S,n,A,P),csg(c,S,G).
  ncg(n,c,g) :- snap(S,n,A,P),csg(c,S,g).

Queries:
  cn('CS101',Name)?
  ncg('Snoopy',Course,Grade)?
  
-----------------------------------------------------
Outputs:

Query Evaluation
cn('CS101',Name)? Yes(3)
  Name='C. Brown'
  Name='P. Patty'
  Name='Snoopy'
ncg('Snoopy',Course,Grade)? Yes(1)
  Course='CS101', Grade='C'
  
C

Example Explained:

Schemes:
-formats the header of the "tables" that will be filled

Facts:
-the information that is filling the "tables

Rules:
-a way to combine "tables" of info in complicated ways that meet a certain ruleset defined by the user

Queries:
-Questions asked by the user about the finished information system

-----------------------------------------------------

Syntax:
        --
Schemes:  |
Facts:    |
Rules:    |------- Marks the info underneath to be processed a certain way 
Queries   |
        --

To insert a Scheme:
  <identifier>(<Column-Name>,<Column-Name>)
  Ex: snap(S,N,A,P)
  
To insert a Fact:
  *adds info to matching table and matching columns
  *column order matters
  <identifier-to-add-to>('<info>','<info>').
  snap('12345','C. Brown','12 Apple St.','555-1234').
    
To insert a Rule:
  <table-to-modify>(<column-id>,<column-id>) :- <table-to-pull-from>(<header-to-pull-from>,<header-to-pull-from>),
      <table-to-pull-from>(<header-to-pull-from>,<header-to-pull-from>)
        
  Ex: Cn(c,n) :- snap(S,n,A,P),csg(c,S,G).
     *takes info in "snap" column "n" and info from "csg" column "c" and inserts it as new info in "Cn"
     *order of colums does matter
  
To insert a Querie:
  <table-to-pull-from>('<data-being-looked-for>',<varible-to-be-returned>)?
  *if data being looked for is inserted as a string, only rows matching that data will be returned
  *variables added act as a "non-specific" piece of data and can be substituted by any values by the program
  *will return info that satisfies the given queries parameters
    
  Ex: cn('CS101',Name)?
    will return:
    Yes (2) <---num of rows that match query
    Name = Luke
    Name = Aiden
