using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using XCharts.Runtime;

public class LineChartUpdater : MonoBehaviour
{
    public LineChart timeDomain;
    private int maxDataPoints = 10;

    // Start is called before the first frame update
    void Start()
    {
        timeDomain = GetComponent<LineChart>();
        var serie = Line.AddDefaultSerie(timeDomain, "Time Domain");
    }

    public void AppendData(int value)
    {
        var serie = timeDomain.GetSerie("Time Domain");
        timeDomain.AddData(serie.index, value);
        if (timeDomain.GetSerie("Time Domain").dataCount > maxDataPoints)
        {
            serie.RemoveData(0);
        }
        timeDomain.RefreshChart();
    }
}