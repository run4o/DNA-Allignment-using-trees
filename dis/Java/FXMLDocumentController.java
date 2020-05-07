/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package fyp;

import java.io.File;
import java.io.FileNotFoundException;
import java.net.URL;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.ResourceBundle;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;

/**
 *
 * @author Martin Trifonov (martin.trifonov98@gmail.com)
 */
public class FXMLDocumentController implements Initializable {

    @FXML
    private LineChart<Number, Number> quality;
    @FXML
    private LineChart<Number, Number> reads;

    @Override
    public void initialize(URL url, ResourceBundle rb) {

        try {
            loadData();
        } catch (FileNotFoundException ex) {
            Logger.getLogger(FXMLDocumentController.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void loadReads() throws FileNotFoundException {
        reads.setCreateSymbols(false);
        NumberAxis x = (NumberAxis) reads.getXAxis();
        NumberAxis y = (NumberAxis) reads.getYAxis();
        x.setAutoRanging(true);
        XYChart.Series series = new XYChart.Series();
        series.setName("Read Length Distribution");
        File file = new File("distribution.dis");
        Scanner in = null;
        try {
            in = new Scanner(file);
        } catch (FileNotFoundException ex) {
            throw new FileNotFoundException("file not found");
        }
        HashMap<Integer, Integer> arr = new HashMap<>();
        int max = 0;
        while (in.hasNextInt()) {
            int score = in.nextInt();

            if (score > max) {
                max = score;
            }
            if (!arr.containsKey(score)) {
                arr.put(score, 1);
            } else {
                arr.replace(score, arr.get(score) + 1);
            }
        }
        for (int i = 0, j = 0; i <= max; i++) {
            if (arr.containsKey(i)) {
                j = arr.get(i);
            } else {
                j = 0;
            }
            series.getData().add(new XYChart.Data<>(i, j));
            j++;
        }
        x.setAutoRanging(false);
        x.setLowerBound(0.0);
        x.setUpperBound(max);
        x.setForceZeroInRange(true);
        reads.getData().add(series);
    }

    private void loadQuality() throws FileNotFoundException {
        quality.setCreateSymbols(false);
        NumberAxis x = (NumberAxis) quality.getXAxis();
        NumberAxis y = (NumberAxis) quality.getYAxis();
        x.setAutoRanging(false);
        x.setLowerBound(0.0);
        x.setUpperBound(40.0);
        x.setTickUnit(1);
        XYChart.Series series = new XYChart.Series();
        series.setName("Read Quality graph");
        File file = new File("quality.dis");
        Scanner in = null;
        try {
            in = new Scanner(file);
        } catch (FileNotFoundException ex) {
            throw new FileNotFoundException("file not found");
        }
        int[] arr = new int[41];
        String str = in.nextLine();
        for (int i = 0; i < str.length(); i++) {
            int score = (int) (str.charAt(i) - '!');
            if (score > 40) {
                score = 40;
            }
            if (score < 0) {
                score = 0;
            }
            arr[score]++;
        }
        int j = 0;
        for (int i : arr) {
            series.getData().add(new XYChart.Data<>(j, i));
            j++;
        }

        quality.getData().add(series);
    }

    private void loadData() throws FileNotFoundException {
        loadReads();
        loadQuality();
    }

}
