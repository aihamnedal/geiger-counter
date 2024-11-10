// components/pages/Visualize.jsx
import React from 'react';
import Graph from '../body/Graph';

function Visualize() {
  return (
    <div
      id="visualize-section"
      className="h-screen flex flex-col items-center justify-start bg-yellow-500 pt-24"
      style={{
        position: 'relative',
      }}
    >
      {/* Overlay */}
      <div
        style={{
          position: 'absolute',
          top: 0,
          left: 0,
          right: 0,
          bottom: 0,
          backgroundColor: 'rgba(0, 0, 0, 0.1)',
          zIndex: 0,
        }}
      />
  
      {/* Heading Text */}
      <h1
        className="text-white text-center font-extrabold"
        style={{
          fontSize: '2rem',
          textShadow: '2px 2px 15px rgba(0, 0, 0, 0.7)',
          padding: '20px 40px',
          backgroundColor: 'rgba(0, 0, 0, 0.4)',
          borderRadius: '12px',
          maxWidth: '80%',
          margin: '0 auto',
          zIndex: 1,
          transition: 'transform 0.3s ease-in-out',
        }}
      >
        Visualize
      </h1>
  
      {/* Add Spacing if Needed */}
      <div className="my-4"></div>
  
      {/* Graph Component */}
      <Graph />
    </div>
  );
}

export default Visualize;
