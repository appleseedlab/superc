package xtc.lang.blink;

import java.util.Stack;

import xtc.lang.JavaEntities;
import xtc.tree.GNode;
import xtc.tree.Node;
import xtc.tree.Visitor;
import xtc.util.Runtime;
import xtc.lang.jeannie.Utilities;

public final class CommandAstAnalyzer extends Visitor {
  enum Language { C, JAVA, DEBUGGER };
  
  private static class MiniVisitor_allNodesHaveLanguage extends Visitor {
    @SuppressWarnings("unused")
    public final void visit(final Node n) {
      assert null != CommandAstAnalyzer.getNodeLanguage(n) : n.toString();
      for (int i=0; i<n.size(); i++)
        if (n.get(i) instanceof Node)
          dispatch(n.getNode(i));
    }
  }

  public static void assertAllNodesHaveLanguage(final Node n) {
    new MiniVisitor_allNodesHaveLanguage().dispatch(n);
  }

  public static Language getNodeLanguage(final Node n) {
    return (Language) n.getProperty("language");
  }

  public static Object getNodeVariableRemap(final Node n) {
    return (Object) n.getProperty("variableRemap");
  }

  private static Language setNodeLanguage(final Node n, final Language language) {
    n.setProperty("language", language);
    return language;
  }

  final Runtime _runtime;
  private final Stack<Language> _stack;

  public CommandAstAnalyzer(final Runtime runtime) {
    assert null != runtime ;
    _runtime = runtime;
    _stack = new Stack<Language>();
    _stack.push(Language.DEBUGGER);
  }

  private boolean assrt(final Node n, final boolean cond, final String msgFormat, final Object... msgArgs) {
    return JavaEntities.runtimeAssrt(_runtime, n, cond, msgFormat, msgArgs);
  }
  
  private final Language currentLanguage() {
    return _stack.peek();
  }

  private final Object dispatchInLanguage(final Node n, final Language language) {
    enterLanguage(language);
    final Object result = dispatch(n);
    exitLanguage(language);
    return result;
  }
  
  private final void enterLanguage(final Language language) {
    _stack.push(language);
  }
  
  private final void exitLanguage(final Language language) {
    assert currentLanguage() == language;
    _stack.pop();
  }
  
  private boolean setAndAssrtLanguage(final Node n, final Language language) {
    setNodeLanguage(n, language);
    return assrt(n, language == currentLanguage(), "expected language %s, current %s", language, currentLanguage());
  }
  
  public final void visit(final GNode n) {
    assrt(n, false, "the Jeannie debugger does not support the %s feature", n.getName());
  }
  
  /** Visit the AbstractDeclarator expression node. */
  public void visitAbstractDeclarator(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit an AdditiveExpression = Expression ("+" / "-") Expression. */
  public final void visitAdditiveExpression(final GNode n) {
    final Language curr = currentLanguage();
    if (assrt(n, curr == Language.C || curr == Language.JAVA, "expected language C or Java, current %s", curr)) {
      setNodeLanguage(n, curr);
      dispatch(n.getNode(0));
      dispatch(n.getNode(2));
    }
  }

  /** Visit an AddressExpression = Expression. */
  public final void visitAddressExpression(final GNode n) {
    if (setAndAssrtLanguage(n, Language.C))
      dispatch(n.getNode(0));
  }

  /** Visit Arguments = Expression*. */
  public final void visitArguments(final GNode n) {
    if (setAndAssrtLanguage(n, Language.JAVA))
      for (int i=0; i<n.size(); i++)
        dispatch(n.getNode(i));
  }

  /** Visit the ArrayDeclarator expression node. */
  public void visitArrayDeclarator(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the ArrayInitializer expression node. */
  public void visitArrayInitializer(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }

  /** Visit an AssignmentExpression = Expression ("=" / "+=" / "-=" / "*=" / "/=" / "%=" / "&lt;&lt;=" / "&gt;&gt;=" / "&amp;=" / "^=" / "|=") Expression. */
  public final void visitAssignmentExpression(final GNode n) {
    if (setAndAssrtLanguage(n, Language.C)) {
      dispatch(n.getNode(0));
      dispatch(n.getNode(2));
    }
  }

  /** Visit the AutoSpecifier expression node. */
  public void visitAutoSpecifier(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the BasicCastExpression expression node. */
  public void visitBasicCastExpression(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }

  /** Visit the BitField expression node. */
  public void visitBitField(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the BitwiseAndExpression expression node. */
  public void visitBitwiseAndExpression(final GNode n) {
    final Language curr = currentLanguage();
    setAndAssrtLanguage(n, curr);
    dispatch(n.getNode(0));
    dispatch(n.getNode(2));
  }

  /** Visit the BitwiseNegationExpression expression node. */
  public void visitBitwiseNegationExpression(final GNode n) {
    final Language curr = currentLanguage();
    setAndAssrtLanguage(n, curr);
  }

  /** Visit the BitwiseOrExpression expression node. */
  public void visitBitwiseOrExpression(final GNode n) {
    final Language curr = currentLanguage();
    setAndAssrtLanguage(n, curr);
    dispatch(n.getNode(0));
    dispatch(n.getNode(2));
  }

  /** Visit the BitwiseXorExpression expression node. */
  public void visitBitwiseXorExpression(final GNode n) {
    final Language curr = currentLanguage();
    setAndAssrtLanguage(n, curr);
    dispatch(n.getNode(0));
    dispatch(n.getNode(2));
  }

  /** Visit the Bool expression node. */
  public void visitBool(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the BooleanLiteral expression node. */
  public void visitBooleanLiteral(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }

  /** Visit a BreakClassCommand = QualifiedIdentifier LineNumber. */
  public final void visitBreakClassCommand(final GNode n) {
    if (setAndAssrtLanguage(n, Language.DEBUGGER)) {
      @SuppressWarnings("unused")
      final String className = (String) dispatchInLanguage(n.getNode(0), Language.JAVA);
    }
  }
  
  /** Visit a BreakClassCommand = QualifiedIdentifier. */
  public final void visitBreakClassMethodCommand(final GNode n) {
    if (setAndAssrtLanguage(n, Language.DEBUGGER)) {
      @SuppressWarnings("unused")
      final String className = (String) dispatchInLanguage(n.getNode(0), Language.JAVA);
    }
  }

  /** Visit a BreakFileCommand = FileName LineNumber. */
  public final void visitBreakFileCommand(final GNode n) {
    setAndAssrtLanguage(n, Language.DEBUGGER);
  }

  /** Visit a BreakFileCommand = FileName LineNumber. */
  public final void visitBreakFunctionCommand(final GNode n) {
    setAndAssrtLanguage(n, Language.DEBUGGER);
  }

  /** Visit a C2jCommand = (no children). */
  public final void visitC2jCommand(final GNode n) {
    setAndAssrtLanguage(n, Language.DEBUGGER);
  }

  /** Visit a CallExpression = [Expression] null MethodName Arguments. */
  public final void visitCallExpression(final GNode n) {
    if (setAndAssrtLanguage(n, Language.JAVA)) {
      if (null != n.get(0))
        dispatch(n.getNode(0));
      @SuppressWarnings("unused")
      final String methodName = n.getString(2);
      dispatch(n.getNode(3));
    }
  }

  /** Visit the CastExpression expression node. */
  public void visitCastExpression(final GNode n) {
    final Language curr = currentLanguage();
    setAndAssrtLanguage(n, curr);
  }

  /** Visit the Char expression node. */
  public void visitChar(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the CharacterConstant expression node. */
  public void visitCharacterConstant(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the CharacterLiteral expression node. */
  public void visitCharacterLiteral(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }
  
  /** Visit a CInJavaExpression = C.UnaryExpression. */
  public final void visitCInJavaExpression(final GNode n) {
    if (setAndAssrtLanguage(n, Language.JAVA))
      dispatchInLanguage(n.getNode(0), Language.C);
  }
  
  /** Visit the ClassLiteralExpression expression node. */
  public void visitClassLiteralExpression(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }
  
  /** Visit the CommaExpression expression node. */
  public void visitCommaExpression(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }
  
  /** Visit the CompoundLiteral expression node. */
  public void visitCompoundLiteral(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the ConcreteDimensions expression node. */
  public void visitConcreteDimensions(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }
  
  /** Visit the ConditionalExpression expression node. */
  public void visitConditionalExpression(final GNode n) {
    final Language curr = currentLanguage();
    setAndAssrtLanguage(n, curr);
    dispatch(n.getNode(0));
    dispatch(n.getNode(1));
    dispatch(n.getNode(2));
  }
  
  /** Visit the ConstantQualifier expression node. */
  public void visitConstantQualifier(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit a ContinueCommand = (no children). */
  public final void visitContinueCommand(final GNode n) {
    setAndAssrtLanguage(n, Language.DEBUGGER);
  }
  
  /** Visit the DeclarationSpecifiers expression node. */
  public void visitDeclarationSpecifiers(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }
  
  /** Visit the Declarator expression node. */
  public void visitDeclarator(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }

  /** Visit the Declarators expression node. */
  public void visitDeclarators(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }

  /** Visit a DeleteCommand = IntegerLiteral. */
  public final void visitDeleteCommand(final GNode n) {
    if (setAndAssrtLanguage(n, Language.DEBUGGER))
      dispatchInLanguage(n.getNode(0), Language.JAVA);
  }

  /** Visit the Dimensions expression node. */
  public void visitDimensions(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }
  
  /** Visit the DirectAbstractDeclarator expression node. */
  public void visitDirectAbstractDeclarator(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }
  
  /** Visit a DirectComponentSelection = Expression String. */
  public final void visitDirectComponentSelection(final GNode n) {
    if (setAndAssrtLanguage(n, Language.C))
      dispatch(n.getNode(0));
  }

  /** Visit the Double expression node. */
  public void visitDouble(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit a DownCommand = IntegerLiteral. */
  public final void visitDownCommand(final GNode n) {
    if (setAndAssrtLanguage(n, Language.DEBUGGER))
      dispatchInLanguage(n.getNode(0), Language.JAVA);
  }

  /** Visit the EnumerationTypeReference expression node. */
  public void visitEnumerationTypeReference(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }
  
  /** Visit the Enumerator expression node. */
  public void visitEnumerator(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the EnumeratorList expression node. */
  public void visitEnumeratorList(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }
  
  /** Visit a EqualityExpression = Expression ("==" / "!=") Expression. */
  public final void visitEqualityExpression(final GNode n) {
    final Language curr = currentLanguage();
    if (assrt(n, curr == Language.C || curr == Language.JAVA, "expected language C or Java, current %s", curr)) {
      setNodeLanguage(n, curr);
      dispatch(n.getNode(0));
      dispatch(n.getNode(2));
    }
  }
  
  /** Visit a ExitCommand = (no children). */
  public final void visitExitCommand(final GNode n) {
    setAndAssrtLanguage(n, Language.DEBUGGER);
  }
  
  /** Visit a Expression = Expression ("=" / "+=" / "-=" / "*=" / "/=" / "&amp;=" / "|=" / "^=" / "%=" / "&lt;&lt;=" / "&gt;&gt;=" / "&gt;&gt;&gt;=") Expression. */
  public final void visitExpression(final GNode n) {
    if (setAndAssrtLanguage(n, Language.JAVA)) {
      dispatch(n.getNode(0));
      dispatch(n.getNode(2));
    }
  }
  
  /** Visit ExpressionList = Expression+. */
  public final void visitExpressionList(final GNode n) {
    if (setAndAssrtLanguage(n, Language.C))
      for (int i=0; i<n.size(); i++)
        dispatch(n.getNode(i));
  }
  
  /** Visit the ExternSpecifier expression node. */
  public void visitExternSpecifier(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the Float expression node. */
  public void visitFloat(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }
  
  /** Visit the FloatingConstant expression node. */
  public void visitFloatingConstant(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }
  
  /** Visit the FloatingPointLiteral expression node. */
  public void visitFloatingPointLiteral(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }
  
  /** Visit a FunctionCall = Expression [ExpressionList]. */
  public final void visitFunctionCall(final GNode n) {
    if (setAndAssrtLanguage(n, Language.C)) {
      dispatch(n.getNode(0));
      if (null != n.get(1))
        dispatch(n.getNode(1));
    }
  }

  /** Visit the FunctionDeclarator expression node. */
  public void visitFunctionDeclarator(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit a GdbCommand = RestOfLine. */
  public final void visitGdbCommand(final GNode n) {
    setAndAssrtLanguage(n, Language.DEBUGGER);
  }

  /** Visit a HelpCommand = (no children). */
  public final void visitHelpCommand(final GNode n) {
    setAndAssrtLanguage(n, Language.DEBUGGER);
  }

  /** Visit the IdentifierList expression node. */
  public void visitIdentifierList(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit an IndirectComponentSelection = Expression -> ID */
  public final void visitIndirectComponentSelection(final GNode n) {
    if (setAndAssrtLanguage(n, Language.C)) {
      dispatch(n.getNode(0));
    }
  }

  /** Visit an IndirectionExpression = Expression. */
  public final void visitIndirectionExpression(final GNode n) {
    if (setAndAssrtLanguage(n, Language.C))
      dispatch(n.getNode(0));
  }

  /** Visit a InfoBreakCommand = (no children). */
  public final void visitInfoBreakCommand(final GNode n) {
    setAndAssrtLanguage(n, Language.DEBUGGER);
  }

  /** Visit a InfoWatchCommand = (no children). */
  public final void visitInfoWatchCommand(final GNode n) {
    setAndAssrtLanguage(n, Language.DEBUGGER);
  }

  /** Visit an InitJCommand = (no children). */
  public final void visitInitJCommand(final GNode n) {
    setAndAssrtLanguage(n, Language.DEBUGGER);
  }

  /** Visit the InstanceOfExpression expression node. */
  public void visitInstanceOfExpression(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }

  /** Visit the InstantiatedType expression node. */
  public void visitInstantiatedType(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }

  /** Visit the Int expression node. */
  public void visitInt(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit an IntegerConstant = String. */
  public final void visitIntegerConstant(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit an IntegerLiteral = String. */
  public final void visitIntegerLiteral(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }

  /** Visit a J2cCommand = (no children). */
  public final void visitJ2cCommand(final GNode n) {
    setAndAssrtLanguage(n, Language.DEBUGGER);
  }

  /** Visit a JavaInCExpression = Java.UnaryExpression. */
  public final void visitJavaInCExpression(final GNode n) {
    if (setAndAssrtLanguage(n, Language.C))
      dispatchInLanguage(n.getNode(0), Language.JAVA);
  }

  /** Visit a JdbCommand = RestOfLine. */
  public final void visitJdbCommand(final GNode n) {
    setAndAssrtLanguage(n, Language.DEBUGGER);
  }

  /** Visit a JRetCommand = (no children). */
  public final void visitJRetCommand(final GNode n) {
    setAndAssrtLanguage(n, Language.DEBUGGER);
  }

  /** Visit a ListCommand = (no children). */
  public final void visitListCommand(final GNode n) {
    setAndAssrtLanguage(n, Language.DEBUGGER);
  }

  /** Visit a LocalsCommand = (no children). */
  public final void visitLocalsCommand(final GNode n) {
    setAndAssrtLanguage(n, Language.DEBUGGER);
  }

  /** Visit the LogicalAndExpression expression node. */
  public void visitLogicalAndExpression(final GNode n) {
    final Language curr = currentLanguage();
    setAndAssrtLanguage(n, curr);
  }

  /** Visit the LogicalNegationExpression expression node. */
  public void visitLogicalNegationExpression(final GNode n) {
    final Language curr = currentLanguage();
    setAndAssrtLanguage(n, curr);
  }

  /** Visit the LogicalOrExpression expression node. */
  public void visitLogicalOrExpression(final GNode n) {
    final Language curr = currentLanguage();
    setAndAssrtLanguage(n, curr);
  }

  /** Visit the Long expression node. */
  public void visitLong(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit a MetaVariable = Identifier. */
  public final void visitMetaVariable(final GNode n) {
    setNodeLanguage(n, Language.DEBUGGER);
    final Language curr = currentLanguage();
    assrt(n, curr == Language.C || curr == Language.JAVA, "expected language C or Java, current %s", curr);
  }

  /** Visit the MultiplicativeExpression expression node. */
  public void visitMultiplicativeExpression(final GNode n) {
    final Language curr = currentLanguage();
    setAndAssrtLanguage(n, curr);
  }

  /** Visit the NewArrayExpression expression node. */
  public void visitNewArrayExpression(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }

  /** Visit the NewClassExpression expression node. */
  public void visitNewClassExpression(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }

  /** Visit a NextCommand = (no children). */
  public final void visitNextCommand(final GNode n) {
    setAndAssrtLanguage(n, Language.DEBUGGER);
  }

  /** Visit an StringLiteral = (no children). */
  public final void visitNullLiteral(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }

  /** Visit the ParameterDeclaration expression node. */
  public void visitParameterDeclaration(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the ParameterList expression node. */
  public void visitParameterList(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the ParameterTypeList expression node. */
  public void visitParameterTypeList(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the Pointer expression node. */
  public void visitPointer(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the PointerDeclarator expression node. */
  public void visitPointerDeclarator(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the PostdecrementExpression expression node. */
  public void visitPostdecrementExpression(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the PostfixExpression expression node. */
  public void visitPostfixExpression(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }

  /** Visit the PostincrementExpression expression node. */
  public void visitPostincrementExpression(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the PredecrementExpression expression node. */
  public void visitPredecrementExpression(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the PreincrementExpression expression node. */
  public void visitPreincrementExpression(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit a PrimaryIdentifier = String. */
  public void visitPrimaryIdentifier(final GNode n) {
    final Language curr = currentLanguage();
    if (assrt(n, curr == Language.C || curr == Language.JAVA, "expected language C or Java, current %s", curr)) {
      setNodeLanguage(n, curr);
    }
  }

  /** Visit the PrimitiveType expression node. */
  public void visitPrimitiveType(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }

  /** Visit a PrintCExpressionCommand = C.Expression. */
  public final void visitPrintCExpressionCommand(final GNode n) {
    if (setAndAssrtLanguage(n, Language.DEBUGGER))
      dispatchInLanguage(n.getNode(0), Language.C);
  }

  /** Visit a PrintJavaExpressionCommand = Java.Expression. */
  public final void visitPrintJavaExpressionCommand(final GNode n) {
    if (setAndAssrtLanguage(n, Language.DEBUGGER))
      dispatchInLanguage(n.getNode(0), Language.JAVA);
  }

  /** Visit a QualifiedIdentifier = Identifier+. */
  public final String visitQualifiedIdentifier(final GNode n) {
    if (!setAndAssrtLanguage(n, Language.JAVA))
      return null;
    return Utilities.qualifiedIdentifierToString(n);
  }

  /** Visit the RelationalExpression expression node. */
  public void visitRelationalExpression(final GNode n) {
    final Language curr = currentLanguage();
    setAndAssrtLanguage(n, curr);
  }

  /** Visit a RunCommand = (no children). */
  public final void visitRunCommand(final GNode n) {
    setAndAssrtLanguage(n, Language.DEBUGGER);
  }

  /** Visit a SelectionExpression = Expression Identifier. */
  public final void visitSelectionExpression(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
    dispatch(n.getNode(0));
    //dispatch(n.getNode(1)); // BK - this is string.
  }

  /** Visit the ShiftExpression expression node. */
  public void visitShiftExpression(final GNode n) {
    final Language curr = currentLanguage();
    setAndAssrtLanguage(n, curr);
  }

  /** Visit the Short expression node. */
  public void visitShort(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the Signed expression node. */
  public void visitSigned(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the SimpleDeclarator expression node. */
  public void visitSimpleDeclarator(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the SizeofExpression expression node. */
  public void visitSizeofExpression(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the SpecifierQualifierList expression node. */
  public void visitSpecifierQualifierList(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit a StatCommand = (no children). */
  public final void visitStatCommand(final GNode n) {
    setAndAssrtLanguage(n, Language.DEBUGGER);
  }

  /** Visit the StaticSpecifier expression node. */
  public void visitStaticSpecifier(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit a StepCommand = (no children). */
  public final void visitStepCommand(final GNode n) {
    setAndAssrtLanguage(n, Language.DEBUGGER);
  }

  /** Visit an StringConstant = String. */
  public final void visitStringConstant(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }

  /** Visit an StringLiteral = String. */
  public final void visitStringLiteral(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }

  /** Visit the StructureDeclaration expression node. */
  public void visitStructureDeclaration(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the StructureDeclarationList expression node. */
  public void visitStructureDeclarationList(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the StructureDeclaratorList expression node. */
  public void visitStructureDeclaratorList(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the StructureTypeDefinition expression node. */
  public void visitStructureTypeDefinition(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the StructureTypeReference expression node. */
  public void visitStructureTypeReference(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit a SubscriptExpression = Expression Expression. */
  public final void visitSubscriptExpression(final GNode n) {
    final Language curr = currentLanguage();
    if (assrt(n, curr == Language.C || curr == Language.JAVA, "expected language C or Java, current %s", curr)) {
      setNodeLanguage(n, curr);
      dispatch(n.getNode(0));
      dispatch(n.getNode(1));
    }
  }

  /** Visit the SuperExpression expression node. */
  public void visitSuperExpression(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }

  /** Visit a ThisExpression = [Expression]. */
  public final void visitThisExpression(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
    assrt(n, null == n.get(0), "the Jeannie debugger does not support qualified this in Java expressions");
  }

  /** Visit the Type expression node. */
  public void visitType(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }

  /** Visit the TypeArguments expression node. */
  public void visitTypeArguments(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }

  /** Visit the TypedefName expression node. */
  public void visitTypedefName(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the TypedefSpecifier expression node. */
  public void visitTypedefSpecifier(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the TypeInstantiation expression node. */
  public void visitTypeInstantiation(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }

  /** Visit the TypeName expression node. */
  public void visitTypeName(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the TypeParameter expression node. */
  public void visitTypeParameter(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }

  /** Visit the TypeParameters expression node. */
  public void visitTypeParameters(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }

  /** Visit the TypeQualifierList expression node. */
  public void visitTypeQualifierList(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the UnaryExpression expression node. */
  public void visitUnaryExpression(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }

  /** Visit the UnaryMinusExpression expression node. */
  public void visitUnaryMinusExpression(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the UnaryPlusExpression expression node. */
  public void visitUnaryPlusExpression(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the UnionTypeDefinition expression node. */
  public void visitUnionTypeDefinition(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the UnionTypeReference expression node. */
  public void visitUnionTypeReference(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the Unsigned expression node. */
  public void visitUnsigned(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit an UpCommand = IntegerLiteral. */
  public final void visitUpCommand(final GNode n) {
    if (setAndAssrtLanguage(n, Language.DEBUGGER))
      dispatchInLanguage(n.getNode(0), Language.JAVA);
  }

  /** Visit the VoidType expression node. */
  public void visitVoidType(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }

  /** Visit the VoidTypeSpecifier expression node. */
  public void visitVoidTypeSpecifier(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit the VolatileQualifier expression node. */
  public void visitVolatileQualifier(final GNode n) {
    setAndAssrtLanguage(n, Language.C);
  }

  /** Visit a WatchCExpressionCommand = C.Expression. */
  public final void visitWatchCExpressionCommand(final GNode n) {
    if (setAndAssrtLanguage(n, Language.DEBUGGER))
      dispatchInLanguage(n, Language.C);
  }

  /** Visit a WatchJavaFieldCommand = [WatchKind] QualifiedIdentifier. */
  public final void visitWatchJavaFieldCommand(final GNode n) {
    if (setAndAssrtLanguage(n, Language.DEBUGGER)) {
      @SuppressWarnings("unused")
      final String className = (String) dispatchInLanguage(n.getNode(1), Language.JAVA);
    }
  }

  /** Visit a WhereCommand = (no children). */
  public final void visitWhereCommand(final GNode n) {
    setAndAssrtLanguage(n, Language.DEBUGGER);
  }

  /** Visit the Wildcard expression node. */
  public void visitWildcard(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }

  /** Visit the WildcardBound expression node. */
  public void visitWildcardBound(final GNode n) {
    setAndAssrtLanguage(n, Language.JAVA);
  }
  
}
