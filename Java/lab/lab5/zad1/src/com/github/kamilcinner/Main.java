package com.github.kamilcinner;

import java.io.File;
import java.io.FilenameFilter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Objects;

public class Main {

    private static <T> void print(T arg) {
        System.out.println(arg);
    }

    private static void endln() {
        print("");
    }

    private static void printList(Object[] list, String title) {
        print(title + " :");
        for (Object item : list) {
            print(item);
        }
    }

    private static void printShortNames(Object[] list) {
        for (Object item : list) {
            int lastDotPosition = item.toString().lastIndexOf('.');
            if (lastDotPosition >= 0) {
                print(item.toString().substring(0, lastDotPosition));
            }
        }
    }

    private static ArrayList<String> findExt(String[] list, String ext) {
        ArrayList<String> filesWithProperExt = new ArrayList<>();
        for (String item : list) {
            if (item.endsWith(ext)) {
                filesWithProperExt.add(item);
            }
        }
        return filesWithProperExt;
    }

    private static ArrayList<String> findCont(String[] list, String subs) {
        ArrayList<String> filesWithProperSubs = new ArrayList<>();
        for (String item : list) {
            if (item.contains(subs)) {
                filesWithProperSubs.add(item);
            }
        }
        return filesWithProperSubs;
    }

    public static void main(String[] args) {
	    File f = new File(".");
	    File[] dirContent = f.listFiles();

	    // Check if the current dir is not empty.
        assert dirContent != null;

        // Add files and dirs names to easier to use ArrayList.
        ArrayList<String> dirFilesNamesAL = new ArrayList<>();
        ArrayList<String> dirDirsNamesAL = new ArrayList<>();

        for (File dirObject : dirContent) {
            if (dirObject.isFile()) {
                dirFilesNamesAL.add(dirObject.getName());
            } else if (dirObject.isDirectory()) {
                dirDirsNamesAL.add(dirObject.getName());
            }
        }

        // Convert ArrayList to simple Array of Strings.
        String[] dirFilesNames = dirFilesNamesAL.toArray(String[]::new);
        String[] dirDirsNames = dirDirsNamesAL.toArray(String[]::new);

        // Print created Arrays.
        printList(dirFilesNames, "Files");
        endln();
        printList(dirDirsNames, "Dirs");
        endln();

        // Print Arrays after sorting.
        // We can see Arrays has been sorted alphabetical.
        Arrays.sort(dirFilesNames);
        printList(dirFilesNames, "Files sorted");
        endln();

        Arrays.sort(dirDirsNames);
        printList(dirDirsNames, "Dirs sorted");
        endln();

        // Print files names without extension eg(.iml).
        print("Files short names:");
        printShortNames(dirFilesNames);
        endln();

        // Find files with (.iml) extension.
        ArrayList<String> imlFiles = findExt(dirFilesNames, ".iml");
        // Print files with (.iml) extension.
        printList(imlFiles.toArray(Object[]::new), "Iml files");
        endln();

        // Find files contain (i) letter.
        ArrayList<String> filesContainLetterI = findCont(dirFilesNames, "i");
        // Print files contain (i) letter.
        printList(filesContainLetterI.toArray(Object[]::new), "Files contain (i) letter");
        endln();
        // Print split result.
        print("Split result:");
        print(filesContainLetterI.toString().split(","));
        endln();
        // Print without split.
        print("Without split:");
        print(filesContainLetterI.toString());
        endln();

        // Print files names without extension eg(.iml)
        // and contain (i) letter.
        print("Files contain (i) letter short names:");
        printShortNames(filesContainLetterI.toArray(Object[]::new));
        endln();

        // Print (src) dir position in dir content.
        // TODO: fix this if necessary because binarySearch returns (-2)
        print("(scr) dir position in dir content:");
//        class fileNameSrcfilter implements FilenameFilter {
//
//            @Override
//            public boolean accept(File file, String s) {
//                return s.equals("src");
//            }
//        }
//        File searchedFile = Objects.requireNonNull(f.listFiles(new fileNameSrcfilter()))[0];
//        print(searchedFile);
        print(Arrays.binarySearch(dirContent, new File("./out")));
    }
}
