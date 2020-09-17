<template>
  <div id="app">
    <!-- <keep-alive> -->
      <router-view :key="key"/>
      <!-- <component /> -->
    <!-- </keep-alive> -->
  </div>
</template>

<script>
export default{
  name: 'App',
  computed: {
    key() {
      return this.$route.path
    }
  }
}
</script>

<style>
html, body, #app {
  height: 100%;
  width: 100%;
  background: #eee
}
</style>

