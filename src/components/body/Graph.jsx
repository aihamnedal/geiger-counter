import React, { useState, useEffect } from 'react';
import Plot from 'react-plotly.js';
import * as d3 from 'd3';

function Graph() {
  const [rows, setRows] = useState([]);

  useEffect(() => { // dummy data
    d3.csv('https://raw.githubusercontent.com/plotly/datasets/master/3d-scatter.csv')
      .then(function(data) {
        console.log('Data loaded:', data);
        setRows(data);
      })
      .catch(function(error) {
        console.error('Error loading the CSV data', error);
      });
  }, []);

  function unpack(rows, key) {
    return rows.map(function(row) {
      return row[key];
    });
  }

  if (rows.length === 0) {
    return <div>Loading...</div>;
  }

  var trace1 = {
    name: "Example Data 1",
    x: unpack(rows, 'x1'),
    y: unpack(rows, 'y1'),
    z: unpack(rows, 'z1'),
    mode: 'markers',
    marker: {
      size: 12,
      line: {
        color: 'rgba(217, 217, 217, 0.14)',
        width: 0.5
      },
      opacity: 0.8
    },
    type: 'scatter3d'
  };

  var trace2 = {
    name: "Example Data 2",
    x: unpack(rows, 'x2'),
    y: unpack(rows, 'y2'),
    z: unpack(rows, 'z2'),
    mode: 'markers',
    marker: {
      color: 'rgb(127, 127, 127)',
      size: 12,
      symbol: 'circle',
      line: {
        color: 'rgb(204, 204, 204)',
        width: 1
      },
      opacity: 0.8
    },
    type: 'scatter3d'
  };

  var data = [trace1, trace2];
  var layout = {
    margin: {
      l: 0,
      r: 0,
      b: 0,
      t: 0
    },
    paper_bgcolor: 'rgba(0,0,0,0)', // Makes the entire plot area transparent
    plot_bgcolor: 'rgba(0,0,0,0)',   // Makes the plotting area (where data is drawn) transparent
    legend: {
        x: 0.8,
        y: 0.9,
        xanchor: 'left',
        yanchor: 'top',
        font: {
          color: '#FFFFFF',
          size: 12,
        },
        bgcolor: 'rgba(0,0,0,0)',
    },
    scene: {
        xaxis: {
          title: {
            text: 'Time', // Set your desired label for the X-axis
            font: {
              color: '#FFFFFF',   // Optional: Adjust the font color
              size: 14            // Optional: Adjust the font size
            }
          },
          backgroundcolor: 'rgba(0,0,0,0)',
          showbackground: false,
          gridcolor: 'rgba(200, 200, 200, 0.3)',
          zerolinecolor: 'rgba(200, 200, 200, 0.5)'
        },
        yaxis: {
          title: {
            text: 'Temperature', // Set your desired label for the Y-axis
            font: {
              color: '#FFFFFF',
              size: 14
            }
          },
          backgroundcolor: 'rgba(0,0,0,0)',
          showbackground: false,
          gridcolor: 'rgba(200, 200, 200, 0.3)',
          zerolinecolor: 'rgba(200, 200, 200, 0.5)'
        },
        zaxis: {
          title: {
            text: 'CPM', // Set your desired label for the Z-axis
            font: {
              color: '#FFFFFF',
              size: 14
            }
          },
          backgroundcolor: 'rgba(0,0,0,0)',
          showbackground: false,
          gridcolor: 'rgba(200, 200, 200, 0.3)',
          zerolinecolor: 'rgba(200, 200, 200, 0.5)'
        }
      }
  };

  return (
    <div>
        <Plot
            data={data}
            layout={layout}
            config={{
                displaylogo: false, // remove Plotly logo
            }}
        />
    </div>
  );
}

export default Graph;
