// Decompile every function in the program to a single C file, plus a function index.
// Usage (headless): -postScript ExportDecomp.java <out_dir>
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;

import java.io.File;
import java.io.PrintWriter;

public class ExportDecomp extends GhidraScript {
    @Override
    protected void run() throws Exception {
        File outDir = new File(getScriptArgs()[0]);
        outDir.mkdirs();

        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(currentProgram);

        try (PrintWriter c = new PrintWriter(new File(outDir, "decomp.c"), "UTF-8");
             PrintWriter idx = new PrintWriter(new File(outDir, "functions.tsv"), "UTF-8")) {
            idx.println("address\tsize\tname\tlibrary");
            for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
                if (monitor.isCancelled()) break;
                boolean lib = f.isThunk() || f.isExternal() || f.getSymbol().getSource().toString().equals("IMPORTED")
                        || f.getName().startsWith("_") || f.getName().startsWith("__") || f.getName().startsWith("Unwind@");
                idx.printf("%s\t%d\t%s\t%s%n", f.getEntryPoint(), f.getBody().getNumAddresses(), f.getName(), lib ? "lib" : "");
                DecompileResults r = decomp.decompileFunction(f, 60, monitor);
                c.printf("// ==== %s @ %s (%d bytes)%s%n", f.getName(), f.getEntryPoint(), f.getBody().getNumAddresses(), lib ? " [lib]" : "");
                c.println(r.decompileCompleted() ? r.getDecompiledFunction().getC() : "// decompile failed: " + r.getErrorMessage());
            }
        }
        decomp.dispose();
    }
}
