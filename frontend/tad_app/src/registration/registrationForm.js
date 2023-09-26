import React, { Component } from 'react';
import './style.css'
import './public/index.html'
class RegistrationPage extends Component {
  constructor() {
    super();
    this.state = {
      name: '',
      age: '',
      sex: 'male',
      orientation: 'straight',
      city: 'unknown',
      bio: '',
      profilePhoto: null,
    };
  }

  handleInputChange = (e) => {
    const { name, value } = e.target;
    this.setState({ [name]: value });
  }

  handleFileChange = (e) => {
    const file = e.target.files[0];
    this.setState({ profilePhoto: file });
  }

  handleSubmit = (e) => {
    e.preventDefault();
    // Send to server
    const handleSubmit  = () => {
        console.log(Name,lastName,email,password,confirmPassword);
    }

    return(
        <div class="container">
        <div class="row main-form">
        <form class="" method="post" action="#">
        
        <div class="form-group">
        <label for="name" class="cols-sm-2 control-label">Your Name</label>
        <div class="cols-sm-10">
        <div class="input-group">
        <span class="input-group-addon"><i class="fa fa-user fa" aria-hidden="true"></i></span>
        <input type="text" class="form-control" name="name" id="name" placeholder="Enter your Name"/>
        </div>
        </div>
        </div>
       
        <div class="form-group">
        <label for="age" class="cols-sm-2 control-label">Your Age</label>
        <div class="cols-sm-10">
        <div class="input-group">
        <span class="input-group-addon"><i class="fa fa-envelope fa" aria-hidden="true"></i></span>
        <input type="number" class="form-control" name="age" id="age" placeholder="Enter your Age"/>
        </div>
        </div>
        </div>
       
        <div class="form-group">
        <label for="sex" class="cols-sm-2 control-label">Sex
        </label>
        <div class="cols-sm-10">
        <div class="input-group">
        <span class="input-group-addon"><i class="fa fa-users fa" aria-hidden="true"></i></span>
        <select type="sex" class="form-control" name="sex" id="sex" placeholder="Select your Sex"
                     name0="sex"
                     value={this.state.sex}
                     onChange={this.handleInputChange}
                   >
                     <option value="male">Man</option>
                     <option value="female">Women</option>
                     <option value="Gay">Vertosexual</option>
                     <option value="Gay">Doublesexual</option>
                     <option value="other">Other</option>
                   </select>
       
        </div>
        </div>
        </div>
       
        <div class="form-group">
        <label for="orientation" class="cols-sm-2 control-label">Orientation
        </label>
        <div class="cols-sm-10">
        <div class="input-group">
        <span class="input-group-addon"><i class="fa fa-users fa" aria-hidden="true"></i></span>
        <select type="orientation" class="form-control" name="orientation" id="orientation" placeholder="Select your Orientation"
                     name1="orientation"
                     value={this.state.orientation}
                     onChange={this.handleInputChange}
                   >
                     <option value="Hetero">Hetero</option>
                     <option value="Bi">Bi</option>
                     <option value="Bi">Gay</option>
                     <option value="Bi">Lesbi</option>
                   </select>
       
        </div>
        </div>
        </div>
       
        <div class="form-group">
        <label for="city" class="cols-sm-2 control-label">City
        </label>
        <div class="cols-sm-10">
        <div class="input-group">
        <span class="input-group-addon"><i class="fa fa-users fa" aria-hidden="false"></i></span>
        <select type="city" class="form-control" name="ciry" id="ciry" placeholder="Select your Citizen"
                     name2="sex"
                     value={this.state.city}
                     onChange={this.handleInputChange}
                   >
                     <option value="male">New Orsk</option>
                     <option value="female">Chechnya</option>
                     <option value="other">Maskvabad</option>
                   </select>
       
        </div>
        </div>
        </div>
        
        <div class="form-group">
        <label for="bio" class="cols-sm-2 control-label">Bio</label>
        <div class="cols-sm-10">
        <div class="input-group">
        <span class="input-group-addon"><i class="fa fa-user fa" aria-hidden="true"></i></span>
        <input type="text" class="form-control" name="bio" id="bio" placeholder="Enter your Bio"/>
        </div>
        </div>
        </div>
       
        <div class="form-group ">
        <a href="#" target="_blank" type="button" id="button" class="btn btn-primary btn-lg btn-block login-button">Start Search</a>
        </div>
        
        </form>
        </div>
        </div>       
    )       
}
}
export default RegistrationForm
