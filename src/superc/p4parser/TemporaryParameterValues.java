package superc.p4parser;
import java.util.ArrayList;
import superc.p4parser.P4LanguageObject.AbstractObjectOfLanguage;

// Temporary value classes
public class TemporaryParameterValues {
    ArrayList<AbstractObjectOfLanguage> parameters;
    ArrayList<AbstractObjectOfLanguage> typeParameters;

    public ArrayList<AbstractObjectOfLanguage> getParameters() {
        return this.parameters;
    }

    public ArrayList<AbstractObjectOfLanguage> getTypeParameters() {
        return this.typeParameters;
    }

    public void addToParameters(AbstractObjectOfLanguage parameter) {
        this.parameters.add(parameter);
    }

    public void addToTypeParameters(AbstractObjectOfLanguage parameter) {
        this.typeParameters.add(parameter);
    }

    public TemporaryParameterValues() {
        this.parameters = new ArrayList<>();
        this.typeParameters = new ArrayList<>();
    }
}