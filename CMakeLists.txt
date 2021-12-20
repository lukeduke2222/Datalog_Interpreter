cmake_minimum_required(VERSION 3.17)
project(Datalog_Interpreter)

set(CMAKE_CXX_STANDARD 14)

add_executable(Datalog_Interpreter main.cpp
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.h
        ColonDashAutomaton.cpp
        Lexer.h
        Lexer.cpp
        Token.h
        Token.cpp
        Automaton.h
        CommaAutomaton.cpp
        CommaAutomaton.h
        PeriodAutomaton.cpp
        PeriodAutomaton.h
        QMarkAutomoton.cpp
        QMarkAutomoton.h
        LeftParenAutomaton.cpp
        LeftParenAutomaton.h
        RightParenAutomaton.cpp
        RightParenAutomaton.h
        MultiplyAutomaton.cpp
        MultiplyAutomaton.h
        MultiplyAutomaton.cpp
        MultiplyAutomaton.h
        AddAutomaton.cpp
        AddAutomaton.h
        RulesAutomaton.cpp
        RulesAutomaton.h
        SchemesAutomaton.cpp
        SchemesAutomaton.h
        FactsAutomaton.cpp
        FactsAutomaton.h
        QueriesAutomaton.cpp
        QueriesAutomaton.h
        IdAutomaton.cpp
        IdAutomaton.h
        StringAutomaton.cpp
        StringAutomaton.h
        CommentAutomaton.cpp
        CommentAutomaton.h
        BlockCommentAutomaton.cpp
        BlockCommentAutomaton.h
        EofAutomaton.cpp
        EofAutomaton.h
        main.cpp
        Parser.cpp
        Parser.h
        DatalogProgram.cpp
        DatalogProgram.h
        Predicates.cpp
        Predicates.h
        Rules.cpp
        Rules.h
        Parameter.cpp
        Parameter.h Relation.cpp Relation.h Tuple.cpp Tuple.h Header.cpp Header.h Database.cpp Database.h Interpreter.cpp Interpreter.h Graph.cpp Graph.h Node.cpp Node.h)