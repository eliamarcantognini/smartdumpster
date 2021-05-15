import React from 'react';
import {
  LineChart, 
  Line,
  XAxis,
  YAxis,
  CartesianGrid,
  Tooltip,
  ResponsiveContainer
} from 'recharts';

const Chart = props => {
  return (
    <div className="card">
      <h2>{props.title}</h2>
      <ResponsiveContainer
        height={300}
      >
        <LineChart
          data={props.data}
          syncId={props.title} 
        >
          <CartesianGrid strokeDasharray="3 3" />
          <XAxis dataKey={props.Xkey} />
          <YAxis type="number" allowDecimals={false}/>
          <Tooltip />
          <Line type="monotone" dataKey={props.Ykey} stroke="#003d33" activeDot={{ r: 8 }} />
        </LineChart>
      </ResponsiveContainer>
    </div>
  );
}

export default Chart;
