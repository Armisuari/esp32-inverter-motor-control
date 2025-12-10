#include "fuzzy_inference.h"

void FuzzyInference::setup()
{
    // FuzzyInput (encoder)
    encoder->addFuzzySet(NB);
    encoder->addFuzzySet(NK);
    encoder->addFuzzySet(Z);
    encoder->addFuzzySet(PK);
    encoder->addFuzzySet(PB);
    _fuzzy->addFuzzyInput(encoder);

    // FuzzyInput (delta error)
    deltaerror->addFuzzySet(TC);
    deltaerror->addFuzzySet(TL);
    deltaerror->addFuzzySet(S);
    deltaerror->addFuzzySet(NL);
    deltaerror->addFuzzySet(NC);
    _fuzzy->addFuzzyInput(deltaerror);

    // FuzzyOutput (frequency)
    frequency->addFuzzySet(KB);
    frequency->addFuzzySet(KS);
    frequency->addFuzzySet(T);
    frequency->addFuzzySet(TS);
    frequency->addFuzzySet(TB);
    _fuzzy->addFuzzyOutput(frequency);

    // Fuzzy rule output
    FuzzyRuleConsequent *thenFrequencyKB = new FuzzyRuleConsequent();
    thenFrequencyKB->addOutput(KB);
    FuzzyRuleConsequent *thenFrequencyKS = new FuzzyRuleConsequent();
    thenFrequencyKS->addOutput(KS);
    FuzzyRuleConsequent *thenFrequencyT = new FuzzyRuleConsequent();
    thenFrequencyT->addOutput(T);
    FuzzyRuleConsequent *thenFrequencyTS = new FuzzyRuleConsequent();
    thenFrequencyTS->addOutput(TS);
    FuzzyRuleConsequent *thenFrequencyTB = new FuzzyRuleConsequent();
    thenFrequencyTB->addOutput(TB);

    // =======================
    // FUZZY RULES DEFINITIONS
    // =======================

    // 1 (NB & TC -> KB)
    FuzzyRuleAntecedent *if_NB_and_TC = new FuzzyRuleAntecedent();
    if_NB_and_TC->joinWithAND(NB, TC);
    FuzzyRule *r1 = new FuzzyRule(1, if_NB_and_TC, thenFrequencyKB);
    _fuzzy->addFuzzyRule(r1);

    // 2 (NB & TL -> KB)
    FuzzyRuleAntecedent *if_NB_and_TL = new FuzzyRuleAntecedent();
    if_NB_and_TL->joinWithAND(NB, TL);
    FuzzyRule *r2 = new FuzzyRule(2, if_NB_and_TL, thenFrequencyKB);
    _fuzzy->addFuzzyRule(r2);

    // 3 (NB & S -> KB)
    FuzzyRuleAntecedent *if_NB_and_S = new FuzzyRuleAntecedent();
    if_NB_and_S->joinWithAND(NB, S);
    FuzzyRule *r3 = new FuzzyRule(3, if_NB_and_S, thenFrequencyKB);
    _fuzzy->addFuzzyRule(r3);

    // 4 (NB & NL -> KS)
    FuzzyRuleAntecedent *if_NB_and_NL = new FuzzyRuleAntecedent();
    if_NB_and_NL->joinWithAND(NB, NL);
    FuzzyRule *r4 = new FuzzyRule(4, if_NB_and_NL, thenFrequencyKS);
    _fuzzy->addFuzzyRule(r4);

    // 5 (NB & NC -> KS)
    FuzzyRuleAntecedent *if_NB_and_NC = new FuzzyRuleAntecedent();
    if_NB_and_NC->joinWithAND(NB, NC);
    FuzzyRule *r5 = new FuzzyRule(5, if_NB_and_NC, thenFrequencyKS);
    _fuzzy->addFuzzyRule(r5);

    // 6 (NK & TC -> KB)
    FuzzyRuleAntecedent *if_NK_and_TC = new FuzzyRuleAntecedent();
    if_NK_and_TC->joinWithAND(NK, TC);
    FuzzyRule *r6 = new FuzzyRule(6, if_NK_and_TC, thenFrequencyKB);
    _fuzzy->addFuzzyRule(r6);

    // 7 (NK & TL -> KS)
    FuzzyRuleAntecedent *if_NK_and_TL = new FuzzyRuleAntecedent();
    if_NK_and_TL->joinWithAND(NK, TL);
    FuzzyRule *r7 = new FuzzyRule(7, if_NK_and_TL, thenFrequencyKS);
    _fuzzy->addFuzzyRule(r7);

    // 8 (NK & S -> KS)
    FuzzyRuleAntecedent *if_NK_and_S = new FuzzyRuleAntecedent();
    if_NK_and_S->joinWithAND(NK, S);
    FuzzyRule *r8 = new FuzzyRule(8, if_NK_and_S, thenFrequencyKS);
    _fuzzy->addFuzzyRule(r8);

    // 9 (NK & NL -> T)
    FuzzyRuleAntecedent *if_NK_and_NL = new FuzzyRuleAntecedent();
    if_NK_and_NL->joinWithAND(NK, NL);
    FuzzyRule *r9 = new FuzzyRule(9, if_NK_and_NL, thenFrequencyT);
    _fuzzy->addFuzzyRule(r9);

    // 10 (NK & NC -> T)
    FuzzyRuleAntecedent *if_NK_and_NC = new FuzzyRuleAntecedent();
    if_NK_and_NC->joinWithAND(NK, NC);
    FuzzyRule *r10 = new FuzzyRule(10, if_NK_and_NC, thenFrequencyT);
    _fuzzy->addFuzzyRule(r10);

    // 11 (Z & TC -> KS)
    FuzzyRuleAntecedent *if_Z_and_TC = new FuzzyRuleAntecedent();
    if_Z_and_TC->joinWithAND(Z, TC);
    FuzzyRule *r11 = new FuzzyRule(11, if_Z_and_TC, thenFrequencyKS);
    _fuzzy->addFuzzyRule(r11);

    // 12 (Z & TL -> KS)
    FuzzyRuleAntecedent *if_Z_and_TL = new FuzzyRuleAntecedent();
    if_Z_and_TL->joinWithAND(Z, TL);
    FuzzyRule *r12 = new FuzzyRule(12, if_Z_and_TL, thenFrequencyKS);
    _fuzzy->addFuzzyRule(r12);

    // 13 (Z & S -> T)
    FuzzyRuleAntecedent *if_Z_and_S = new FuzzyRuleAntecedent();
    if_Z_and_S->joinWithAND(Z, S);
    FuzzyRule *r13 = new FuzzyRule(13, if_Z_and_S, thenFrequencyT);
    _fuzzy->addFuzzyRule(r13);

    // 14 (Z & NL -> TS)
    FuzzyRuleAntecedent *if_Z_and_NL = new FuzzyRuleAntecedent();
    if_Z_and_NL->joinWithAND(Z, NL);
    FuzzyRule *r14 = new FuzzyRule(14, if_Z_and_NL, thenFrequencyTS);
    _fuzzy->addFuzzyRule(r14);

    // 15 (Z & NC -> TS)
    FuzzyRuleAntecedent *if_Z_and_NC = new FuzzyRuleAntecedent();
    if_Z_and_NC->joinWithAND(Z, NC);
    FuzzyRule *r15 = new FuzzyRule(15, if_Z_and_NC, thenFrequencyTS);
    _fuzzy->addFuzzyRule(r15);

    // 16 (PK & TC -> T)
    FuzzyRuleAntecedent *if_PK_and_TC = new FuzzyRuleAntecedent();
    if_PK_and_TC->joinWithAND(PK, TC);
    FuzzyRule *r16 = new FuzzyRule(16, if_PK_and_TC, thenFrequencyT);
    _fuzzy->addFuzzyRule(r16);

    // 17 (PK & TL -> T)
    FuzzyRuleAntecedent *if_PK_and_TL = new FuzzyRuleAntecedent();
    if_PK_and_TL->joinWithAND(PK, TL);
    FuzzyRule *r17 = new FuzzyRule(17, if_PK_and_TL, thenFrequencyT);
    _fuzzy->addFuzzyRule(r17);

    // 18 (PK & S -> TS)
    FuzzyRuleAntecedent *if_PK_and_S = new FuzzyRuleAntecedent();
    if_PK_and_S->joinWithAND(PK, S);
    FuzzyRule *r18 = new FuzzyRule(18, if_PK_and_S, thenFrequencyTS);
    _fuzzy->addFuzzyRule(r18);

    // 19 (PK & NL -> TS)
    FuzzyRuleAntecedent *if_PK_and_NL = new FuzzyRuleAntecedent();
    if_PK_and_NL->joinWithAND(PK, NL);
    FuzzyRule *r19 = new FuzzyRule(19, if_PK_and_NL, thenFrequencyTS);
    _fuzzy->addFuzzyRule(r19);

    // 20 (PK & NC -> TB)
    FuzzyRuleAntecedent *if_PK_and_NC = new FuzzyRuleAntecedent();
    if_PK_and_NC->joinWithAND(PK, NC);
    FuzzyRule *r20 = new FuzzyRule(20, if_PK_and_NC, thenFrequencyTB);
    _fuzzy->addFuzzyRule(r20);

    // 21 (PB & TC -> TS)
    FuzzyRuleAntecedent *if_PB_and_TC = new FuzzyRuleAntecedent();
    if_PB_and_TC->joinWithAND(PB, TC);
    FuzzyRule *r21 = new FuzzyRule(21, if_PB_and_TC, thenFrequencyTS);
    _fuzzy->addFuzzyRule(r21);

    // 22 (PB & TL -> TS)
    FuzzyRuleAntecedent *if_PB_and_TL = new FuzzyRuleAntecedent();
    if_PB_and_TL->joinWithAND(PB, TL);
    FuzzyRule *r22 = new FuzzyRule(22, if_PB_and_TL, thenFrequencyTS);
    _fuzzy->addFuzzyRule(r22);

    // 23 (PB & S -> TB)
    FuzzyRuleAntecedent *if_PB_and_S = new FuzzyRuleAntecedent();
    if_PB_and_S->joinWithAND(PB, S);
    FuzzyRule *r23 = new FuzzyRule(23, if_PB_and_S, thenFrequencyTB);
    _fuzzy->addFuzzyRule(r23);

    // 24 (PB & NL -> TB)
    FuzzyRuleAntecedent *if_PB_and_NL = new FuzzyRuleAntecedent();
    if_PB_and_NL->joinWithAND(PB, NL);
    FuzzyRule *r24 = new FuzzyRule(24, if_PB_and_NL, thenFrequencyTB);
    _fuzzy->addFuzzyRule(r24);

    // 25 (PB & NC -> TB)
    FuzzyRuleAntecedent *if_PB_and_NC = new FuzzyRuleAntecedent();
    if_PB_and_NC->joinWithAND(PB, NC);
    FuzzyRule *r25 = new FuzzyRule(25, if_PB_and_NC, thenFrequencyTB);
    _fuzzy->addFuzzyRule(r25);
}

bool FuzzyInference::setInput(int fuzzyInputIndex, float crispValue)
{
    if (_fuzzy->setInput(fuzzyInputIndex, crispValue))
        return false;
    return true;
}

bool FuzzyInference::fuzzify()
{
    if (_fuzzy->fuzzify())
        return false;
    return true;
}

float FuzzyInference::defuzzify(int fuzzyOutputIndex)
{
    return _fuzzy->defuzzify(fuzzyOutputIndex);
}