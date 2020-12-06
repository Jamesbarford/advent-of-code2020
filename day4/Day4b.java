import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;

public class Day4b {
    public static void main(String[] args) {
        FileReaderByLineb fileReaderByLine = new FileReaderByLineb("input.txt");
        System.out.println(fileReaderByLine.readByLines());
    }
}

class FileReaderByLineb {
    private final HashMap<String, String> passportFields = new HashMap<>();
    private final String path;
    private int validCount = 0;

    public FileReaderByLineb(String path) {
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
                    this.passportFields.clear();
                } else {
                    for (String splitLine : splitLines) {
                        String[] keyValue = splitLine.split(":");

                        this.passportFields.put(keyValue[0], keyValue[1]);
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
        Validatorb validator = new Validatorb(this.passportFields);
        System.out.println(this.passportFields);
        if (validator.isValid()) {
            validCount++;
        }
    }
}

class Validatorb {
    private final HashMap<String, String> passportFields;
    private final HashSet<String> mandatoryFields = new HashSet<>(Arrays.asList("byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"));
    private final HashSet<String> validEyeColors = new HashSet<>(Arrays.asList("amb", "blu", "brn", "gry", "grn", "hzl", "oth"));

    public Validatorb(HashMap<String, String> fields) {
        this.passportFields = fields;
    }

    public boolean isValid() {
        boolean isValidKeys = this.passportFields.keySet().containsAll(this.mandatoryFields);

        boolean isValidValue = false;

        for (HashMap.Entry<String, String>entry : this.passportFields.entrySet()) {
            String key = entry.getKey();
            String value = entry.getValue();

            isValidValue = this.check(key, value);
            if (!isValidValue) {
                System.out.println("invalid value :: " + value);
                return false;
            }
        }
        System.out.println(isValidValue && isValidKeys);
        return isValidValue && isValidKeys;
    }

    private <T> boolean check(String key, T value) {
        String strVal = (String)value;
        switch (key) {
            case "byr" -> {
                int valToCheck = Integer.parseInt(strVal);
                return valToCheck >= 1920 && valToCheck <= 2002;
            }
            case "iyr" -> {
                int valToCheck = Integer.parseInt(strVal);
                return valToCheck >= 2010 && valToCheck <= 2020;
            }
            case "eyr" -> {
                int valToCheck = Integer.parseInt(strVal);
                return valToCheck >= 2020 && valToCheck <= 2030;
            }
            case "hgt" -> {
                if (strVal.contains("cm")) {
                    int height = Integer.parseInt(strVal.replace("cm", ""));
                    return height >= 150 && height <= 193;
                } else if (strVal.contains("in")) {
                    int height = Integer.parseInt(strVal.replace("in", ""));
                    return height >= 59 && height <= 76;
                } else {
                    return false;
                }
            }
            case "hcl" -> {
                if (!strVal.startsWith("#")) {
                    return false;
                }

                String santized = strVal.replace("#", "");

                return santized.length() == 6 && santized.matches("^[0-9A-Fa-f]+$");
            }
            case "ecl" -> {
                return this.validEyeColors.contains(strVal);
            }
            case "pid" -> {
                boolean isValidLength = strVal.length() == 9;
                if (!isValidLength) {
                    return false;
                }

                try {
                    Integer.parseInt(strVal);
                    return true;
                } catch (NumberFormatException e) {
                    return false;
                }
            }

            case "cid" -> {
                return true;
            }

            default -> {
                return false;
            }
        }
    }
}