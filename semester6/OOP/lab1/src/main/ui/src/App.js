import './App.css';
import { Component } from 'react';
import { BrowserRouter, Route, Switch } from 'react-router-dom';
import Form from './Form.jsx'
import ManagerWorkspace from './ManagerWorkspace.jsx'
import ClientWorkspace from './ClientWorkspace.jsx'

function App() {
  return (
    <BrowserRouter>
      <div className = "App">
        <Switch>

          {/* <Route exact path = '/' component = {Form}/> */}
          <Route exact path = '/' component = {ClientWorkspace}/>
          <Route path = '/m_u=*' component = {ManagerWorkspace}/>
        </Switch>
      </div>
    </BrowserRouter>
  );
  // history.
  return;
}

export default App;
