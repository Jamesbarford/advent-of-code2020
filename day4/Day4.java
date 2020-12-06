import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;

public class Day4 {
    public static void main(String[] args) {
        FileReaderByLine fileReaderByLine = new FileReaderByLine("input.txt");
        System.out.println(fileReaderByLine.readByLines());
    }
}

class FileReaderByLine {
    private final ArrayList<String> currentFields = new ArrayList<>();
    private final String path;
    private int validCount = 0;

    public FileReaderByLine(String path) {
        this.path = path;
    }

    public int readByLines() {
        BufferedReader reader;
        try {
            reader = new BufferedReader(new FileReader(this.path));
            String line = reader.readLine();

            while (line != null) {
                String[] splitLines = line.split(" ");
                boolean newPerson = splitLines[0].equals("");

                if (newPerson) {
                    this.validate();
                    this.currentFields.clear();
                } else {
                    for (String splitLine : splitLines) {
                        String[] keyValue = splitLine.split(":");

                        this.currentFields.add(keyValue[0]);
                    }
                }

                line = reader.readLine();
            }
            this.validate();
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return this.validCount;
    }

    private void validate() {
        Validator validator = new Validator(this.currentFields);
        if (validator.isValid()) {
            validCount++;
        }
    }
}

class Validator {
    private final ArrayList<String> fields;
    private final HashSet<String> mandatoryFields = new HashSet<>(Arrays.asList("byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"));

    public Validator(ArrayList<String> fields) {
        this.fields = fields;
    }

    public Boolean isValid() {
        return this.fields.containsAll(this.mandatoryFields);
    }
}