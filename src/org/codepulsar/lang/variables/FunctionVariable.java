package org.codepulsar.lang.variables;

import org.codepulsar.lang.Instruction;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedHashMap;

public class FunctionVariable {
    private LinkedHashMap<String, Function> variables;

    public FunctionVariable() {
        this.variables = new LinkedHashMap<>();
    }

    public void addFunction(String name, int arity) {
        this.variables.put(name, new Function(arity));
    }

    public void setChunk(String name, ArrayList<Instruction> chunk) {
        this.variables.get(name).setChunk(chunk);
    }

    public HashMap<String, Function> getVariables() {
        return this.variables;
    }

    public static class Function {
        private ArrayList<Instruction> chunk;
        private int arity;

        public Function(int arity) {
            this.chunk = null;
            this.arity = arity;
        }

        public ArrayList<Instruction> getChunk() {
            return this.chunk;
        }

        public void setChunk(ArrayList<Instruction> chunk) {
            this.chunk = chunk;
        }
    }
}
