
#include "Parser.h"

Parser::Parser(std::vector<Token*> tokens) {
    for (unsigned int i = 0; i < tokens.size(); i++) {
        dataTokens.push_back(tokens.at(i));
    }
}

void Parser::Parse() {
    try {
        ParseDatalog();
        //std::cout << "Success!" << std::endl;
        //addToDatalog.toString();
        //added in attempt to fix bug

    } catch (Token* error) {
        //std::cout << "Failure!" << std::endl;
        //std::cout << "  " <<  error->toString() << std::endl;
    }
}

void Parser::ParseDatalog() {
    //datalogProgram -> SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF
    Match(TokenType::SCHEMES);
    Match(TokenType::COLON);
    scheme();
    schemeList();
    Match(TokenType::FACTS);
    Match(TokenType::COLON);
    factList();
    Match(TokenType::RULES);
    Match(TokenType::COLON);
    rulesList();
    Match(TokenType::QUERIES);
    Match(TokenType::COLON);
    query();
    queryList();
    Match(TokenType::END_OF_FILE);
}

void Parser::scheme() {
    //scheme -> ID LEFT_PAREN ID idList RIGHT_PAREN
    tmpPredicate = new Predicates;
    Match(TokenType::ID);
    tmpPredicate->addName(dataTokens.at(currToken-1)->GetDescription());

    Match(TokenType::LEFT_PAREN);
    Match(TokenType::ID);
    tmpPredicate->addParameter(dataTokens.at(currToken-1)->GetDescription());

    idList();
    Match(TokenType::RIGHT_PAREN);
    addToDatalog.addScheme(tmpPredicate);
}

void Parser::schemeList() {
    //schemeList -> scheme schemeList | lambda
    if (dataTokens.at(currToken)->type == TokenType::ID) {
        scheme();
        schemeList();
    } else if (dataTokens.at(currToken)->type == TokenType::FACTS) {
        //lambda
    } else {
        throw dataTokens.at(currToken);
    }
}

void Parser::factList() {
    //factList	->	fact factList | lambda
    if (dataTokens.at(currToken)->type == TokenType::ID) {
        fact();
        factList();
    } else if (dataTokens.at(currToken)->type == TokenType::RULES) {
        //lambda
    } else {
        throw dataTokens.at(currToken);
    }
}

void Parser::query() {
    //query -> predicate Q_MARK
    tmpPredicate = new Predicates();

    addToDatalog.addQuery(queryPredicate());
    Match(TokenType::Q_MARK);
}

void Parser::queryList() {
    //queryList	->	query queryList | lambda
    if (dataTokens.at(currToken)->type == TokenType::ID) {
        query();
        queryList();
    } else if (dataTokens.at(currToken)->type == TokenType::END_OF_FILE) {
        //lambda
    } else {
        throw dataTokens.at(currToken);
    }
}

void Parser::fact() {
    //fact -> ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
    tmpPredicate = new Predicates;

    Match(TokenType::ID);
    tmpPredicate->addName(dataTokens.at(currToken-1)->GetDescription());
    Match(TokenType::LEFT_PAREN);
    Match(TokenType::STRING);
    tmpPredicate->addParameter(dataTokens.at(currToken-1)->GetDescription());

    stringList();
    Match(TokenType::RIGHT_PAREN);
    Match(TokenType::PERIOD);
    addToDatalog.addFact(tmpPredicate);

}

void Parser::stringList() {
    //stringList -> COMMA STRING stringList | lambda
    if (dataTokens.at(currToken)->type == TokenType::COMMA) {
        Match(TokenType::COMMA);
        Match(TokenType::STRING);
        tmpPredicate->addParameter(dataTokens.at(currToken-1)->GetDescription());

        stringList();
    } else if (dataTokens.at(currToken)->type == TokenType::RIGHT_PAREN) {
        //lambda
    } else {

        throw dataTokens.at(currToken);
    }
}

void Parser::rulesList() {
    //ruleList	->	rule ruleList | lambda
    if (dataTokens.at(currToken)->type == TokenType::ID) {
        rule();
        rulesList();
    } else if (dataTokens.at(currToken)->type == TokenType::QUERIES) {
        //lambda
    } else {
        throw dataTokens.at(currToken);
    }
}

void Parser::rule() {
    //rule -> headPredicate COLON_DASH predicate predicateList PERIOD
    tmpRule = new Rules();
    tmpPredicate = new Predicates();
    tmpRule->addHead(headPredicate());

    Match(TokenType::COLON_DASH);
    tmpRule->addBody(predicate());
    predicateList();
    Match(TokenType::PERIOD);
    addToDatalog.addRule(tmpRule);
}

Predicates Parser::headPredicate() {
    //headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
    rulePredicate.clear();

    Match(TokenType::ID);
    rulePredicate.addName(dataTokens.at(currToken-1)->GetDescription());
    Match(TokenType::LEFT_PAREN);
    Match(TokenType::ID);
    rulePredicate.addParameter(dataTokens.at(currToken-1)->GetDescription());

    idList();
    Match(TokenType::RIGHT_PAREN);
    return rulePredicate;
}

Predicates Parser::predicate() {
    //predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    rulePredicate.clear();
    Match(TokenType::ID);
    rulePredicate.addName(dataTokens.at(currToken-1)->GetDescription());

    Match(TokenType::LEFT_PAREN);
    rulePredicate.addParameter(parameter());

    parameterList();
    Match(TokenType::RIGHT_PAREN);
    return rulePredicate;
}

Predicates* Parser::queryPredicate() {
    //predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    tmpPredicate->clear();
    Match(TokenType::ID);
    tmpPredicate->addName(dataTokens.at(currToken-1)->GetDescription());

    Match(TokenType::LEFT_PAREN);
    tmpPredicate->addParameter(parameter());

    parameterList();
    Match(TokenType::RIGHT_PAREN);
    return tmpPredicate;
}

void Parser::predicateList() {
    //predicateList	->	COMMA predicate predicateList | lambda
    if (dataTokens.at(currToken)->type == TokenType::COMMA) {
        Match(TokenType::COMMA);
        tmpRule->addBody(predicate());
        predicateList();
    } else if (dataTokens.at(currToken)->type == TokenType::PERIOD) {
        //lambda
    } else {
        throw dataTokens.at(currToken);
    }
}

std::string Parser::parameter() {
    //parameter	->	STRING | ID
    if (dataTokens.at(currToken)->type == TokenType::STRING) {
        Match(TokenType::STRING);
        return dataTokens.at(currToken-1)->GetDescription();
    } else if (dataTokens.at(currToken)->type == TokenType::ID) {
        Match(TokenType::ID);
        return dataTokens.at(currToken-1)->GetDescription();
    } else {
        throw dataTokens.at(currToken);
    }
}

void Parser::parameterList() {
    //parameterList	-> 	COMMA parameter parameterList | lambda
    if (dataTokens.at(currToken)->type == TokenType::COMMA) {
        Match(TokenType::COMMA);
//        tmpPredicate->addParameter(parameter());
        std::string param = parameter();
        tmpPredicate->addParameter(param);
        rulePredicate.addParameter(param);
        parameterList();
    } else if (dataTokens.at(currToken)->type == TokenType::RIGHT_PAREN) {
        //lambda
    } else {
        throw dataTokens.at(currToken);
    }
}

void Parser::idList() {
    //idList -> COMMA ID idList | lambda
    if (dataTokens.at(currToken)->type == TokenType::COMMA) {
        Match(TokenType::COMMA);
        Match(TokenType::ID);
//        std::string param = parameter();
         tmpPredicate->addParameter(dataTokens.at(currToken-1)->GetDescription());
         rulePredicate.addParameter(dataTokens.at(currToken-1)->GetDescription());
//        tmpPredicate->addParameter(dataTokens.at(currToken-1)->GetDescription());
        idList();
    } else if (dataTokens.at(currToken)->type == TokenType::RIGHT_PAREN) {
        //lambda
    } else {
        throw dataTokens.at(currToken);
    }
}



void Parser::Match(TokenType typeToMatch) {
    if (currToken >= dataTokens.size()) {
        throw dataTokens.at(currToken);
    }
    if (dataTokens.at(currToken)->type == typeToMatch) {
        currToken++;
    } else {
        throw dataTokens.at(currToken);
    }
}

std::vector<Predicates*> Parser::GetDatalogSchemes() {
    return addToDatalog.GetSchemes();
}

std::vector<Predicates*> Parser::GetDatalogFacts() {
    return addToDatalog.GetFacts();
}

std::vector<Predicates*> Parser::GetDatalogQueries() {
    return addToDatalog.GetQueries();
}
std::vector<Rules*> Parser::GetDatalogRules() {
    return addToDatalog.GetRules();
}