import './App.css';
import { Component } from 'react';
import { BrowserRouter, Route, Switch } from 'react-router-dom';
import Form from './Form.jsx'
import LibrarianWorkspace from './LibrarianWorkspace.jsx'
import ClientWorkspace from './ClientWorkspace.jsx'

function App() {
  return (
    <BrowserRouter>
      <div className = "App">
        <Switch>

          <Route exact path = '/' component = {Form}/>
          <Route path = '/l_u=*' component = {LibrarianWorkspace}/>
          <Route path = '/c_u=*' component = {ClientWorkspace}/>
        </Switch>
      </div>
    </BrowserRouter>
  );
  return;
}

export default App;
